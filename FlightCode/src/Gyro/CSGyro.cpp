

#include "CSGyro.h"

CSGyro::CSGyro() {
    
}

void CSGyro::config() {
    Wire.begin();
    
    imu.calibrateMPU9250(imu.gyroBias, imu.accelBias);
    imu.initMPU9250();
    imu.initAK8963(imu.magCalibration);
}

GyroData_t CSGyro::getData() {
    // Cool, works. Lines 215 - 222 in MPU9250BasicAHRS.ino
    
    // Init stuff
    imu.readGyroData(imu.gyroCount);  // Read the x/y/z adc values 
    imu.getGres();

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    imu.gx = (float)imu.gyroCount[0]*imu.gRes;
    imu.gy = (float)imu.gyroCount[1]*imu.gRes;
    imu.gz = (float)imu.gyroCount[2]*imu.gRes;
    
    GyroData_t g;
    g.x = imu.gx;
    g.y = imu.gy;
    g.z = imu.gz;
    
    return g;
}

AccelData_t CSGyro::getAccelData() {
    imu.readAccelData(imu.accelCount);
    imu.getAres();
    
    imu.ax = (float)imu.accelCount[0]*imu.aRes;
    imu.ay = (float)imu.accelCount[1]*imu.aRes;
    imu.az = (float)imu.accelCount[2]*imu.aRes;
    
    AccelData_t a;
    a.x = imu.ax;
    a.y = imu.ay;
    a.z = imu.az;
    
    return a;
}