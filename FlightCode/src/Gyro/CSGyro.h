
#ifndef _csgyro_h
#define _csgyro_h

// extern "C"
// {
//   #include "avr_i2c.h"
// }

// #include "mpu9250.h"
// #include "SparkFunIMU.h"
#include "MPU9250.h"

typedef struct {
    float x;
    float y;
    float z;
} GyroData_t;

typedef struct {
    float x;
    float y;
    float z;
} AccelData_t;

class CSGyro {
public:
    // Init
    CSGyro();
    void config();
    
    // Vars
    
    // Funcs
    GyroData_t getData();
    AccelData_t getAccelData();
    
private:
    // MPU_9250 myIMU;
    MPU9250 imu;
};


#endif