
#include <Arduino.h>

#include <SD.h>
#include "CSSDCard.h"

CSSDCard::CSSDCard() {
    
}

void CSSDCard::config(const char* fname) {
    filename = fname;
    
    // Init SD Card
    int tries = 10;
    while (tries > 0) {
        // Wait for init ?
        delay(100);
        Serial.println("SD initializing...");
        
        if (SD.begin(BUILTIN_SDCARD)) {
            break;
        }
        
        tries--;
    }
    
    if (tries == 0) {
        Serial.println("Failed to initialize");
    } else {
        Serial.println("SD initialized");
    }
    
}

void CSSDCard::write(String s) {
    File dataFile = SD.open(filename, FILE_WRITE);
    
    if (dataFile) {
        dataFile.println(s);
        dataFile.close();
    } else {
        Serial.println("SD: Unable to write to " + String(filename) + "!");
    }
}