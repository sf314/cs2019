
#include "CSBme.h"

CSBme bme;


void setup() {
    Serial.begin(9600);
    bme.config();
    pinMode(13, OUTPUT);
}

int light = 0;
void loop() {
    Serial.println(bme.readAlt());
    
    if (light) {
        digitalWrite(13, HIGH);
        light = 0;
    } else {
        digitalWrite(13, LOW);
        light = 1;
    }
    delay(1000);
}