

#include "Arduino.h"


class CSTemp {
public:
    CSTemp();
    void config(int p);
    float read();
private:
    int pin;
};