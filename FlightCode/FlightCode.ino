/**
 * CanSat 2019 Flight Code
 * Stephen Flores
 * 
 * Responsible for all software-related flight operations
 * Fully autonomous, with command override capability
 * Auto-recovery from power loss using SD and/or EEPROM
 * 
 * v0.1: Serial heartbeat "Hello, world", unformatted tx packets
 * 
 */

// ********** Libraries 
#include "MissionConfig.h"
#include <SoftwareSerial.h>

// ********** Global data, i.e. hardware
SoftwareSerial radio(CS_RADIO_MISO_PIN, CS_RADIO_MOSI_PIN);




// ********** Setup
void setup() {
    Serial.begin(9600);
    radio.begin(9600);
    
    pinMode(CS_LED_PIN, OUTPUT);
}

// ********** Loop
void loop() {
    
}
