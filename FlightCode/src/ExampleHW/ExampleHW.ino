/*
Example Hardware driver

Usage:
Create a directory for your hardware in `src`
Make a test file of the same name as the directory, with the `.ino` extension
Make your `.cpp` and `.h` files, with `CS` as the prefix
Add any library files, if there are any, with relative-path `#include`s

Write your test code in the `.ino` file
Access your code from `FlightCode` using relative-path `#include`
*/

#include "CSExampleHW.h"

CSExampleHW myHardware;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting test for Example Hardware...");
    
    myHardware.init(4);
}

void loop() {
    float data = myHardware.getData();
    Serial.println(data);
    delay(1000);
}
