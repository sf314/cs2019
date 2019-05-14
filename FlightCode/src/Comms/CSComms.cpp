
#include "CSComms.h"

CSComms::CSComms(void) {
    radio = NULL;
}

void CSComms::setRadio(SoftwareSerial* newRadio) {
    radio = newRadio;
}

void CSComms::println(String s) {
    // Print through serial and radio
    Serial.println(s);
    radio->println(s);
}

void CSComms::txTelem(CSTelem t) {
    Serial.println(t.toString());
    radio->println(t.toString());
}

void CSComms::txAlert(String s) {
    Serial.println("Alert," + s);
    radio->println("Alert," + s);
}