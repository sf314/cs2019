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

// ********** Global data, i.e. hardware
SoftwareSerial radio(CS_RADIO_MISO_PIN, CS_RADIO_MOSI_PIN);
SoftwareSerial gpsss(CS_GPS_MISO_PIN, CS_GPS_MOSI_PIN);
unsigned long currentTime = 0;
unsigned long prevTime = 0;

// Hardware 
CSBme bme;
CSGps gps(&gpsss);
CSGyro gyro;



// ********** Setup
void setup() {
    Serial.begin(9600);
    radio.begin(9600);
    gps.begin(9600);

    pinMode(CS_LED_PIN, OUTPUT);

    bme.config();
    gyro.config();
}

// ********** Loop
void loop() {
    // Update time
    currentTime = millis();

    // Update GPS and other async functions
    gps.update();

    if (currentTime - prevTime >= 1000) {
        prevTime = currentTime;
        GyroData_t gyroData = gyro.getData();

        Serial.println("USB: alt = " + String(bme.readAlt()));
        Serial.println("USB: temp = " + String(bme.readTemp()));
        Serial.println("USB: press = " + String(bme.readPressure()));
        Serial.println("USB: GPS time = " + String(gps.time));
        Serial.println("USB: GPS sats = " + String(gps.satellites));
        Serial.println("USB: GPS lat = " + String(gps.lat));
        Serial.println("USB: GPS lon = " + String(gps.lon));
        Serial.println("USB: Gyro X = " + String(gyroData.x));
        Serial.println();

        radio.println("Radio: alt = " + String(bme.readAlt()));
        radio.println("Radio: temp = " + String(bme.readTemp()));
        radio.println("Radio: press = " + String(bme.readPressure()));
        radio.println("Radio: GPS time = " + String(gps.time));
        radio.println("Radio: Gyro X = " + String(gyroData.x));
        radio.println();
    }


}
