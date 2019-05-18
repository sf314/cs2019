
#include <Arduino.h>
#include "CSHall.h"

// Fileprivate var
volatile int CSHall_count = 0;

CSHall::CSHall(void) {
    CSHall_count = 0;
    pin = 0;
}

void CSHall::config(int p) {
    // Setup callback function and things on that pin 
    attachInterrupt(p, increment, RISING);
    pin = p;
}

int CSHall::getCurrentCount(void) {
    return CSHall_count;
}

static void CSHall::increment(void) {
    CSHall_count++;
}

void CSHall::clearCount(void) {
    CSHall_count = 0;
}