
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "CSSDCard.h"

CSSDCard sdCard;

void setup() {
    Serial.begin(9600);
    sdCard.config("myFile.txt");
}

void loop() {
    delay(1000);
    Serial.println("Writing");
    sdCard.write("Hey " + String(millis()));
}