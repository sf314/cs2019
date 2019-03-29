
#include "CSNichrome.h"

CSNichrome nichrome;

void setup() {
    Serial.begin(9600);
    nichrome.config(14);
}

void loop() {
    
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'a':
                Serial.println("Starting burn...");
                nichrome.start();
                break;
            case 'f':
                Serial.println("Stopping burn...");
                nichrome.stop();
                break;
            default:
                Serial.println("Bad command " + String(c));
                nichrome.stop();
                break;
        }
    }
    
    
}