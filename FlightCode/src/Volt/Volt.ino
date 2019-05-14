
#include "CSVolt.h"

CSVolt volt;

void setup() {
    Serial.begin(9600);

    volt.config(5); // Some arbitrary pin to test
}

void loop() {
    Serial.println("Current voltage: " + String(volt.read()));
    delay(1000);
}