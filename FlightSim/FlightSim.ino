/**
 * Flight Simulator
 * For testing serial communication with a ground station
 * Shall implement regular (fake telem)
 * Shall implement alerts 
 * Shall implement commanding 
 */


#include <Arduino.h>

// ********** Vars 
unsigned long t_now;
unsigned long t_prev;

// ********** Forward declarations 
void pt_command_ingest(void);

void setup() {
    Serial.begin(9600);
}

int packetCount = 0;

void loop() {
    t_now = millis();
    
    // Do pseudothreads
    pt_command_ingest();
    
    if (t_now - t_prev >= 1000) {
        // Send fake telem 
        Serial.println("3623," + String(packetCount) + ".0," + String(packetCount) + ",1000,1013,20,3.3,123.5,33.5,-111.9,1410,3,0.01,0.0,9.4,3");
        
        packetCount++;
        t_prev = t_now;
    }
    
    
}


void pt_command_ingest() {
    if (Serial.available()) {
        char c = Serial.read();
        
        switch (c) {
            case 'g':
                Serial.println("Alert,Setting ground height");
                break;
            case 'q':
                Serial.println("Alert,Starting cut");
                break;
            case 'w':
                Serial.println("Alert,Stopping cut");
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
                Serial.println("Alert,Switched to state " + String(c));
                break;
            default:
                Serial.println("Alert,Unrecognized command " + String(c));
                break;
        }
    }
}