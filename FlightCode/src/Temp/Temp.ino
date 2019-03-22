

#include "CSTemp.h"

CSTemp temp;

void setup() {
    temp.config(5);
}

void loop() {
    Serial.println(temp.read());
    delay(1000);
}