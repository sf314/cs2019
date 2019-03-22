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

// ********** Global data, i.e. hardware
SoftwareSerial radio(CS_RADIO_MISO_PIN, CS_RADIO_MOSI_PIN);
SoftwareSerial gpsss(CS_GPS_MISO_PIN, CS_GPS_MOSI_PIN);
unsigned long currentTime = 0;
unsigned long prevTime = 0;

// Hardware 
CSBme bme;
CSGps gps(&gpsss);



// ********** Setup
void setup() {
    Serial.begin(9600);
    radio.begin(9600);
    gps.begin(9600);

    pinMode(CS_LED_PIN, OUTPUT);

    bme.config();
}

// ********** Loop
void loop() {
    // Update time
    currentTime = millis();

    // Update GPS and other async functions
    gps.update();

    if (currentTime - prevTime >= 1000) {
        prevTime = currentTime;

        Serial.println("USB: alt = " + String(bme.readAlt()));
        Serial.println("USB: temp = " + String(bme.readTemp()));
        Serial.println("USB: press = " + String(bme.readPressure()));
        Serial.println("USB: GPS time = " + String(gps.time));
        Serial.println();

        radio.println("USB: alt = " + String(bme.readAlt()));
        radio.println("USB: temp = " + String(bme.readTemp()));
        radio.println("USB: press = " + String(bme.readPressure()));
        radio.println("USB: GPS time = " + String(gps.time));
        radio.println();
    }


}
