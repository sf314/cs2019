
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
    
    // Init arr
    for (int i = 0; i < 9; i++) {
        arr[i] = 0;
    }
}

void CSHall::config(int p) {
    // Setup callback function and things on that pin 
    // Serial.println("Configuring with pin " + String(p));
    pin = p;
    pinMode(p, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(p), update, RISING);
}

float CSHall::getRpm() {
    
    // Every second, shift values down, then log current count to index zero, Reset counter to zero
    
    // Shift values down 
        for (int i = 8; i > 0; i--) {
            arr[i] = arr[i - 1];
        }

        arr[0] = hitCount;
    
    // Calculate each bucket
        int bucket1 = arr[0] - arr[4];
        int bucket2 = arr[1] - arr[5];
        int bucket3 = arr[2] - arr[6];
        int bucket4 = arr[3] - arr[7];
        
        
    // calculate RPM
        float average = (bucket1 + bucket2 + bucket3 + bucket4) / 4.0;
        float rpm = average * 15.0;
    
    // Serial.println("Hitcount = " + String(hitCount));
    
    Serial.print("CSHall.arr: ");
    for (int i = 0; i < 9; i++) {
        Serial.print(String(arr[i]) + ",");
    }
    Serial.println();
    return rpm;
}

static void update() { 
    Serial.println("hitCount increment " + String(hitCount));
    
    hitCount++;

}
