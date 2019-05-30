/**
 * CanSat 2019 Flight Code
 * Stephen Flores
 * 
 * Responsible for all software-related flight operations
 * Fully autonomous, with command override capability
 * Auto-recovery from power loss using SD and/or EEPROM
 * 
 * v0.1: Serial heartbeat "Hello, world", unformatted tx packets
 * 
 */

// ********** Libraries 
#include "MissionConfig.h"
#include <SoftwareSerial.h>

#include "src/GPS/CSGps.h"
#include "src/BME/CSBme.h"
#include "src/Gyro/CSGyro.h"
#include "src/Nichrome/CSNichrome.h"
#include "src/Volt/CSVolt.h"
#include "src/Hall/CSHall.h"
#include "src/Temp/CSTemp.h"
#include "src/Telem/CSTelem.h"
#include "src/Comms/CSComms.h"
#include "src/CoreData/CSCoreData.h"
#include "src/SDCard/CSSDCard.h"

// ********** Global data, i.e. hardware
SoftwareSerial radio(CS_RADIO_MISO_PIN, CS_RADIO_MOSI_PIN);
SoftwareSerial gpsss(CS_GPS_MISO_PIN, CS_GPS_MOSI_PIN);
unsigned long currentMS = 0;
unsigned long prevMS = 0;
unsigned long startTime = 0; // time (seconds) since epoch
bool ledOn = false;


// Hardware 
CSBme bme;
CSGps gps(&gpsss);
CSGyro gyro;
CSVolt volt;
CSHall hall;
CSTemp temp;
CSNichrome nichrome;
CSComms comms;
CSCoreData coreData;
CSSDCard sd;

CSTelem telem;

// Function prototypes
void handleCommands(char c);
void verifyState(void);

// States
void task_launchpad(void);
void task_ascent(void);
void task_descent();
void task_release(void);
void task_landed(void);

// ********** Setup
void setup() {
    Serial.begin(9600);
    radio.begin(9600);
    gps.begin(9600);

    coreData.config();
    
    comms.setRadio(&radio);

    pinMode(CS_LED_PIN, OUTPUT);

    bme.config();
    gyro.config();
    volt.config(CS_VOLT_PIN);
    nichrome.config(CS_NICHROME_PIN);
    temp.config(CS_TEMP_PIN);
    hall.config(CS_HALL_PIN);
    sd.config("TELEM.TXT");
    
    // Read data from coreData to init system on bootup
    float groundAlt = coreData.readFloat(CDKEY_GROUND_ALT);
    bme.setGroundAlt(groundAlt);
}

// ********** Loop
void loop() {
    // Update time
    currentMS = millis();
    
    // Handle commands 
    if (Serial.available()) {
        handleCommands(Serial.read());
    }
    
    if (radio.available()) {
        handleCommands(radio.read());
    }

    // Update GPS and other async functions
    gps.update();

    nichrome.update();

    if (currentMS - prevMS >= 1000) {
        
        GyroData_t gyroData = gyro.getData();

        float met; // Float or double?
        if (gps.time < 1.00) { // GPS has not received lock
            // Count up from saved GPS time?
            // Retrieve previous GPS time, then add (currentMS / 1000)
        } else {
            // Use GPS time as met 
            met = gps.time;
            // Save this time to CoreData (4 bytes)
        }

        telem.teamId = 3623;
        // telem.met = gps.getTime() - startTime;
        telem.met = currentMS / 1000; // Simple, for now
        telem.packetCount++; // Does not need to be set manually here // <- what?

        float newAlt = bme.readAlt();
        telem.__velocity = newAlt - telem.altitude;
        telem.altitude = newAlt;

        telem.pressure = bme.readPressure();
        telem.temp = bme.readTemp();
        telem.voltage = volt.read();
        telem.gpsTime = gps.time; // Rely on GPS time more!
        telem.gpsLat = gps.lat;
        telem.gpsLon = gps.lon;
        telem.gpsAlt = gps.altitude;
        telem.gpsSats = gps.satellites;
        telem.pitch = gyroData.x; // x or y? Both?
        telem.roll = gyroData.z; // Spin rate along z axis?
        telem.bladeSpinRate = hall.getCurrentCount(); hall.clearCount(); // Keep track of hall sensor hits
        // telem.state; // Does not need to be set manually here
        
        // Transmit telem over serial and radio and SD
        comms.txTelem(telem); // Should be done in individual state task
        sd.write(telem.toString());

        // check state and perform modifications as necessary
        verifyState();
        
        // Set time for next loop
        prevMS = currentMS;
        
        // Change light state 
        if (ledOn) {
            digitalWrite(CS_LED_PIN, LOW);
            ledOn = false;
        } else {
            digitalWrite(CS_LED_PIN, HIGH);
            ledOn = true;
        }
        
    }


}


void handleCommands(char c) {
    switch (c) {
    case 'g': 
        {
            float newGroundAlt = bme.readAltRaw();
            bme.setGroundAlt(newGroundAlt);
            coreData.writeFloat(CDKEY_GROUND_ALT, newGroundAlt);
            comms.txAlert("Setting new ground height to " + String(newGroundAlt));
        }
        break;
    case 'q':
        {
            comms.txAlert("Forcing cut");
            nichrome.start();
        }
        break;
    case 'w':
        {
            comms.txAlert("Ending cut");
            nichrome.stop();
        }
    default:
        break;
    }
}


void verifyState() {
    // Check state and perform modifications if necessary 
    switch (telem.state) {
        case STATE_LAUNCHPAD:
            task_launchpad();
            break;
        case STATE_ASCENT:
            task_ascent();
            break;
        case STATE_DESCENT:
            task_descent();
            break;
        case STATE_RELEASE:
            task_release();
            break;
        case STATE_LANDED: 
            task_landed();
            break;
        default:
            comms.txAlert("Bad state value " + String(telem.state));
            break;
    }
}

// States
void task_launchpad() {
    // Wait until velocity is high and you're above alt thresh
    if (telem.__velocity > CS_ASCENT_VEL_THRESH && telem.altitude > CS_GROUND_ALT_THRESH) {
        telem.state = STATE_ASCENT;
        comms.txAlert("Now ascending");
    }

    comms.txTelem(telem);
}

void task_ascent() {
    // Wait until you're descending 
    if (telem.__velocity < CS_DESCENT_VEL_THRESH) {
        telem.state = STATE_DESCENT;
        comms.txAlert("Now descending");
    }

    comms.txTelem(telem);
}

void task_descent() {
    // Handle release trigger 
    if (telem.altitude < CS_DEPLOY_ALT) {
        telem.state = STATE_RELEASE;
        nichrome.start(); // Will handle itself automatically 
        comms.txAlert("Now releasing");
    }

    comms.txTelem(telem);
}

void task_release() {
    // Wait until you've landed 
    if (telem.altitude < CS_GROUND_ALT_THRESH && telem.__velocity > CS_DESCENT_VEL_THRESH) {
        telem.state = STATE_LANDED;
        comms.txAlert("Now landing");
    }

    comms.txTelem(telem);
}

void task_landed() {
    // Anything?

    // Play a buzzer 

}