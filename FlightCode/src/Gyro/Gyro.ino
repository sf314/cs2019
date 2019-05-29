

#include "CSGyro.h"
CSGyro gyro;


#define USE_COMMS 1
#define USE_SD 1

#if USE_COMMS==1
#include <SoftwareSerial.h>
SoftwareSerial radio(0, 1);
#endif

#if USE_SD==1
#include "CSSDCard.h"
CSSDCard sdCard;
#endif


void setup() {
    delay(500);
    Serial.begin(9600);
    Serial.println("Gyro test");
    
    #if USE_COMMS==1
    radio.begin(9600);
    #endif
    
    #if USE_SD==1
    sdCard.config("datafile.csv");
    #endif
    
    gyro.config();
    Serial.println("Starting loop...");
}

void loop() {
    // Serial.println("Getting data...");
    // GyroData_t gdata = gyro.getData(); // REGULAR TEST DATA
    // Serial.println("Got data");
    // String dataString;
    // dataString = String(gdata.x) + ", ";
    // dataString += String(gdata.y) + ", ";
    // dataString += String(gdata.z);
    // Serial.println(dataString);
    // delay(250);
    
    
    
    // NEW TEST DATA FOR ACCELERATION
    // Constantly spit out accel data (x/y/z and magnitude)
    
    AccelData_t a = gyro.getAccelData();
    double mag = sqrt((a.x*a.x) + (a.y*a.y) + (a.z*a.z));
    String telem = 
        String(millis()) + "," + 
        String(a.x) + "," + 
        String(a.y) + "," + 
        String(a.z) + "," + 
        String(mag);
        
    Serial.println(telem);
    
    #if USE_COMMS==1
    radio.println(telem);
    #endif
    
    #if USE_SD==1
    sdCard.write(telem);
    #endif
}