// Test the GPS Module

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "CSGps.h"

// Things that shall exist in the global scope:
SoftwareSerial gpsss(7, 8); // Rx, Tx (MISO, MOSI)
// Adafruit_GPS agps(&gpsss);
CSGps gps(&gpsss);

void setup() {
    Serial.begin(9600);
    gps.begin(9600);
    gps.shouldDebug = false;
    delay(1000);
    Serial.println("GPS start");
    Serial.println("Test Vector start");
    
    CSVector vector;
    vector.push_back("One");
    vector.push_back("Two");
    vector.push_back("Three");
    vector.printAll();
    
    Serial.println("Examining: ");
    Serial.println(vector.at(0));
    Serial.println(vector.at(1));
    Serial.println(vector.at(2));
    Serial.println(vector.at(1));
    Serial.println(vector.at(0));
    
    
    vector.destroy();
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    // // Keep track of time constantly
    currentTime = millis();
    
    // // Update GPS constantly
    gps.update();
    // if (gps.available()) {
    //     Serial.print(gps.read());
    // }
    
    // Periodically print data
    if (currentTime - previousTime >= 1000) {
        // Pretend main code here
        Serial.println("Main!");
        
        // Do things for other subsystems
        // ...
        
        // Print GPS status stuff
        Serial.println(gps.time);
        Serial.println(gps.altitude);
        previousTime = currentTime;
    }

    // if (gpsss.available()) {
    //     while (gpsss.available()) {
    //         char c = gpsss.read();
    //         Serial.print(c);
    //     }
    // }
    
}




//$GPGGA,033549.000,3212.9924,N,09811.3520,W,1,04,1.87,172.9,M,-22.9,M,,*54
//$GPGGA,040829.000,3212.9917,N,09811.3485,W,2,05,1.32,295.1,M,-22.9,M,0000,0000*5B