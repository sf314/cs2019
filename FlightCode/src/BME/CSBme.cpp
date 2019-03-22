

#include "CSBme.h"

Adafruit_BME280 internalBme(10);

CSBme::CSBme() {
    groundAlt = 0.0;
}

void CSBme::config() {
    // Config sensor here
    int status = internalBme.begin();
    if (status != 0) {
        Serial.println("CSBme: internal BME280 failed to init, status code is " + String(status));
    }
}

float CSBme::readAlt() { // Metres
    return internalBme.readAltitude(SEALEVELPRESSURE_HPA) - groundAlt;
}

float CSBme::readAltRaw() { // Metres
    return internalBme.readAltitude(SEALEVELPRESSURE_HPA);
}

float CSBme::readTemp() { // Celsius
    return internalBme.readTemperature();
}

float CSBme::readPressure() { // Hecto pascals
    return internalBme.readPressure() / 100.0F;
}

void CSBme::setGroundAlt(float newAlt) {
    groundAlt = newAlt;
}

