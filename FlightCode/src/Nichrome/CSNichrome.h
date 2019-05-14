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
    void start();
    void stop();
    void update();
private:
    int pin;
    bool isActive;
    unsigned long startMillis;
};


#endif 