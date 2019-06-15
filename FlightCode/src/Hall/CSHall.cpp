
#include <Arduino.h>
#include "CSHall.h"

// Fileprivate var
// volatile int CSHall_count = 0;
volatile float CSHall_rpm = 0.0;
volatile unsigned long CSHall_time = 0;
volatile unsigned long previous2 = 0;
volatile unsigned long previous1 = 0;
volatile unsigned long currentTime = 0;
volatile unsigned long hitCount = 0;

static void update(void);

CSHall::CSHall(void) {
    pin = 0;
}

void CSHall::config(int p) {
    // Setup callback function and things on that pin 
    // Serial.println("Configuring with pin " + String(p));
    pin = p;
    pinMode(p, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(p), update, RISING);
}

float CSHall::getRpm() {
    // If it's been more than a second since the last ping, decay the value (?) - old
    // This will achieve RPM that is below 60 - old

    // anything less than 60 hits per second is longer than one second
    // 1 hit every 3 seconds is 20 rpm
    // 1 hit every 5 seconds is 12 rpm lower bound
    
    // queue of past 3 millis values
    previous2 = previous1;
    previous1 = currentTime;
    currentTime = millis();

    // average of past 3 values
    unsigned long movingAverageMillis = (previous2 + previous1 + currentTime) / 3;
    movingAverageMillis = 1 / movingAverageMillis;
    movingAverageMillis *= 1000;

    //set test_rpm
    CSHall_rpm = movingAverageMillis * 60;
    
    /*
    if (currentTime - CSHall_time >= 1000) {
        unsigned long delta_time = currentTime - CSHall_time;
        float test_rpm = (1000.0 / delta_time) * 60.0 / 2;
        
        if (test_rpm < 10) {
            return 0.0;
        }
        
        return test_rpm;
    }
    */
    
    // threshold to consider blades not spinning, set rpm to 0
    if (currentTime > 5000) {
        CSHall_rpm = 0;
    }
    return CSHall_rpm;

    currentTime++;

    if(currentTime % 5 == 0) {
        currentTime = 0;
    }

}

static void update() { 
    
        // // Calculate time delta
        // unsigned long current_time = millis();
        // unsigned long delta_time = current_time - CSHall_time;
        
        // if (delta_time < 200) {
        //     return;
        // }
        
        // // Update RPM value 
        // CSHall_rpm = (1000.0 / delta_time) * 60.0;
        
        // // Update time
        // CSHall_time = current_time;
        
        // // Serial.println("interrupt: update RPM @ delt = " + String(delta_time));

    // increment a counter instead
    hitCount++;

}
