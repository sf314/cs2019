
#include <Arduino.h>
#include "CSHall.h"
#define HALL_THRESHOLD 64

CSHall hall;

int hallPin = 14;

void setup() {
    Serial.begin(9600);
    pinMode(hallPin, INPUT);
    hall.config(hallPin);
}

void loop() {

    delay(1000);
    Serial.println(hall.getCurrentCount());
    hall.clearCount();
    
    // // Read constantly from sensor (analog)
    // int value = analogRead(hallPin);
    // Serial.print("Val: " + String(value));
    
    // if (value > HALL_THRESHOLD) {
    //     Serial.println(" -- HALL TRIGGERED");
    // }
    
    // Serial.println();


}