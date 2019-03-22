
#include "CSTemp.h"


CSTemp::CSTemp() { 
    pin = 0; // Default pin
}

void CSTemp::config(int p) {
    pin = p;
}

float CSTemp::read() {
    // Convert 
    return analogRead(pin);
}