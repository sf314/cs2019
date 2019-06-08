
#include <Arduino.h>
#include "CSHall.h"
#define HALL_THRESHOLD 350

CSHall hall;

int hallPin = 20;

void setup() {
    Serial.begin(9600);
    hall.config(hallPin);
}

void loop() {

    // ***** Read from interrupt at 1Hz
    delay(1000);
    Serial.println(hall.getRpm());
    
    // ***** Read constantly from sensor (analog)
    // int value = analogRead(hallPin);
    // Serial.print("Val: " + String(value));
    
    // if (value > HALL_THRESHOLD) {
    //     Serial.println(" -- HALL TRIGGERED");
    // }
    
    // Serial.println();


}