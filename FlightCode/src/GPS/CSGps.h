// CSGps header file
// Stephen Flores

#ifndef CSGps_h
#define CSGps_h

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>
#include <SoftwareSerial.h>


typedef struct StringNode_t {
    String s;
    StringNode_t* next;
} StringNode_t;

class CSVector { // vector of Strings
    public:
    CSVector();
    void push_back(String s);
    String at(int i);
    void destroy();
    void printAll();
    
    StringNode_t* head;
    int count;
};


class CSGps {
public:
    // CSGps(Adafruit_GPS* agps); // Init
    CSGps(SoftwareSerial* ss);
    void update();
    void begin(int baud);
    void parsePacket();
    void debugln(String s);
    
    bool available();
    char read();
    
    // Meta
    int satellites;
    float altitude;
    bool fix;
    
    // Position: Degrees
    double lat;
    double lon;
    
    // Time: 
    double time;
    // uint8_t hour, minute, seconds, year, month, day;

    
    bool shouldDebug;
    String temp;
    bool packetReceived;
private:
    // Adafruit_GPS* adaGpsPtr;
    SoftwareSerial* serial;
};


#endif