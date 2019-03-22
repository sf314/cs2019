#ifndef CSBME_H
#define CSBME_H

#include "Arduino.h"

#include "Adafruit_BME280.h"

#define SEALEVELPRESSURE_HPA 1013.25

class CSBme {
public:
    CSBme();
    void config();

    float readAlt();
    float readAltRaw();
    float readTemp();
    float readPressure();

    void setGroundAlt(float newAlt);
private:
    float groundAlt;
};

#endif