
#include "CSNichrome.h"


CSNichrome::CSNichrome() {
    
}

void CSNichrome::config(int p) {
    pin = p;
    isActive = false;
    startMillis = 0;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void CSNichrome::start() {
    digitalWrite(pin, HIGH);
    startMillis = millis();
    isActive = true;
}

void CSNichrome::stop() {
    digitalWrite(pin, LOW);
    isActive = false;
}

void CSNichrome::update() {
    // Enforce 10-second max cut time for safety
    if (millis() - startMillis >= 10000) {
        // Exceeded burn limit. Auto-shutoff
        digitalWrite(pin, LOW);
        isActive = false;
    }
}