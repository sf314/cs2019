
#include <Arduino.h>
#include "CSVolt.h"

CSVolt::CSVolt() {
    pin = 0; // Default
    sampleSize = 1;
}

void CSVolt::config(int p) {
    pin = p;
    pinMode(p, INPUT);
    sampleSize = 1;
}

void CSVolt::setSampleSize(int newSize) {
    sampleSize = newSize;
}

float CSVolt::read() {
    float sum = 0;
    for (int index = 0; index < sampleSize; index++) {
        float x = analogRead(pin); // * 3.3 / 1024.0;
        sum += x;
        delay(10);
    }
    
    float average = sum / sampleSize;
    
    float volt = average / 4095.0 * 3.3;
    float volt2 = (volt * 32.0 / 10);// - 0.32; // * 3.2?
    float result = volt2 - 0.325;
    return result;
}