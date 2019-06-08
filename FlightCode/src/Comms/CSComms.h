
#ifndef _CSCOMMS_H
#define _CSCOMMS_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../Telem/CSTelem.h"

class CSComms {
public:
    CSComms(void);
    void setRadio(SoftwareSerial* newRadio);

    void println(String s); // Direct access 

    void txTelem(CSTelem t);
    void txTelem(String s);
    void txAlert(String s); 
private:
    SoftwareSerial* radio;
};

#endif 