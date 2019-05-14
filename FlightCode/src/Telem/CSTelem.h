
#ifndef _CSTELEM_H
#define _CSTELEM_H

#include <Arduino.h>

class CSTelem {
public:
    // Init 
    CSTelem();
    
    // Telem fields
    int teamId = 3623;
    float met = 0.0;
    int packetCount = 0;
    float altitude = 0.0;
    float pressure = 0.0;
    float temp = 0.0;
    float voltage = 0.0;
    double gpsTime = 0.0;
    float gpsLat = 0.00;
    float gpsLon = 0.00;
    float gpsAlt = 0.00;
    int gpsSats = 0;
    float pitch = 0.0;
    float roll = 0.0;
    float bladeSpinRate = 0.0;
    int state = 0;
    
    // Access
    String toString(void);
private:
    
};

#endif 