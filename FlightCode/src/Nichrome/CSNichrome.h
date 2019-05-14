/**
 * CanSat Nichrome Subsystem
 * Stephen Flores
 * 2019/03/29
 */

#ifndef _CSNICHROME_H
#define _CSNICHROME_H

#include "Arduino.h"

class CSNichrome {
public:
    CSNichrome(void);
    
    void config(int p);
    void setMaxCutTime(int ms);
    void start();
    void stop();
    void update();

    bool isActive;
private:
    int pin;
    unsigned long startMillis;
    int maxCutTime;
};


#endif 