
#include <Arduino.h>
#include "CSHall.h"

// Fileprivate var
volatile int CSHall_count = 0;
static void increment(void);

CSHall::CSHall(void) {
    CSHall_count = 0;
    pin = 0;
}

void CSHall::config(int p) {
    // Setup callback function and things on that pin 
    // Serial.println("Configuring with pin " + String(p));
    attachInterrupt(digitalPinToInterrupt(p), increment, FALLING);
    pin = p;
}

int CSHall::getCurrentCount(void) {
    Serial.println("blade spin rate: " + String(CSHall_count));
    return CSHall_count;
}

static void increment() { /// ?
    Serial.println("interrupt: increment");
    CSHall_count++;
}

void CSHall::clearCount(void) {
    CSHall_count = 0;
}