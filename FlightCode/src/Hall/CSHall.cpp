

#include "CSHall.h"

CSHall::CSHall(void) {
    count = 0;
    pin = 0;
}

void CSHall::config(int p) {
    // Setup callback function and things on that pin 
    pin = p;
}

int CSHall::getCurrentCount(void) {
    return count;
}

void CSHall::increment(void) {
    count++;
}

void CSHall::clearCount(void) {
    count = 0;
}