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

// ********** Global data, i.e. hardware
SoftwareSerial radio(CS_RADIO_MISO_PIN, CS_RADIO_MOSI_PIN);
SoftwareSerial gpsss(CS_GPS_MISO_PIN, CS_GPS_MOSI_PIN);
unsigned long currentMS = 0;
unsigned long prevMS = 0;
unsigned long startTime = 0; // time (seconds) since epoch


// Hardware 
CSBme bme;
CSGps gps(&gpsss);
CSGyro gyro;
CSTelem telem;
CSVolt volt;
CSHall hall;
CSTemp temp;
CSNichrome nichrome;

// Function prototypes
void handleCommands(char c);

// ********** Setup
void setup() {
    Serial.begin(9600);
    radio.begin(9600);
    gps.begin(9600);

    pinMode(CS_LED_PIN, OUTPUT);

    bme.config();
    gyro.config();
    volt.config(CS_VOLT_PIN);
    nichrome.config(CS_NICHROME_PIN);
    temp.config(CS_TEMP_PIN);
    hall.config(CS_HALL_PIN);
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

        telem.teamId = 3623;
        // telem.met = gps.getTime() - startTime;
        telem.met = currentMS / 1000;
        // telem.packetCount; // Does not need to be set manually here
        telem.altitude = bme.readAlt();
        telem.pressure = bme.readPressure();
        telem.temp = bme.readTemp();
        telem.voltage = volt.read();
        telem.gpsTime = gps.time;
        telem.gpsLat = gps.lat;
        telem.gpsLon = gps.lon;
        telem.gpsAlt = gps.altitude;
        telem.gpsSats = gps.satellites;
        // telem.pitch = gyro.getPitch(); // Spin rate along x and y?
        // telem.roll = gyro.getRoll(); // Spin rate along z axis?
        telem.bladeSpinRate = hall.getCurrentCount(); hall.clearCount(); // Keep track of hall sensor hits
        // telem.state; // Does not need to be set manually here
        
        // Transmit telem over serial and radio
        Serial.println(telem.toString());
        radio.println(telem.toString());
        
        // Set time for next loop
        prevMS = currentMS;
    }


}


void handleCommands(char c) {
    switch (c) {
    case 'g':
        Serial.println("Setting ground height...");
        break;
    case 'q':
        Serial.println("Forcing cut");
        nichrome.start();
        break;
    case 'w':
        Serial.println("Ending cut");
        nichrome.stop();
    default:
        break;
    }
}