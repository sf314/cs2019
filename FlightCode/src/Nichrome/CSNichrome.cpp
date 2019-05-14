
#include "CSNichrome.h"


CSNichrome::CSNichrome() {
    isActive = false;
    startMillis = 0;
    maxCutTime = 7000;
}

void CSNichrome::config(int p) {
    pin = p;

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
    if (millis() - startMillis >= maxCutTime) {
        // Exceeded burn limit. Auto-shutoff
        digitalWrite(pin, LOW);
        isActive = false;
    }
}