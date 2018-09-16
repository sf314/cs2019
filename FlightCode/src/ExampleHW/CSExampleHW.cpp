
#include "CSExampleHW.h"

void CSExampleHW::init(int p) {
    pin = p;
}

float CSExampleHW::getData() {
    // Read hardware and do calculations here
    float someData = analogRead(pin);
    return someData * 3.14; 
}
