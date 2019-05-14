

#include "Arduino.h"


class CSTemp {
public:
    CSTemp();
    void config(int p);
    void config(int p, int mv); // Voltage in millivolts
    float read();
    int readRaw();
private:
    int pin;
    int voltage;
};