
#include <Arduino.h>
#define HALL_THRESHOLD 64

int hallPin = 14;

void setup() {
    Serial.begin(9600);
    pinMode(hallPin, INPUT);
}

void loop() {
    
    // Read constantly from sensor (analog)
    int value = analogRead(hallPin);
    Serial.print("Val: " + String(value));
    
    if (value > HALL_THRESHOLD) {
        Serial.println(" -- HALL TRIGGERED");
    }
    
    Serial.println();
}