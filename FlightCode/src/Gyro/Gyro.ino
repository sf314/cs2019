

#include "CSGyro.h"
CSGyro gyro;

void setup() {
    Serial.begin(9600);
    
    Serial.println("Gyro test");
    gyro = CSGyro();
}

void loop() {
    GyroData_t gdata = gyro.getData();
    String dataString;
    dataString = String(gdata.x) + ", ";
    dataString += String(gdata.y) + ", ";
    dataString += String(gdata.z);
    Serial.println(dataString);
    delay(250);
}