
#include "CSNichrome.h"


CSNichrome::CSNichrome() {
    
}

void CSNichrome::config(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void CSNichrome::start() {
    digitalWrite(pin, HIGH);
}

void CSNichrome::stop() {
    digitalWrite(pin, LOW);
}

