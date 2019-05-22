// CSCoreData header file
// Stephen Flores
// DOES NOT ACCOUNT FOR HASH COLLISIONS!

#include <Arduino.h>
#include <EEPROM.h>

class CSCoreData {
public:
    // initialization
    CSCoreData(); 
    void config();
    void debugMode(bool b);
    void deleteAll();
    
    // writing
    void writeLong(String key, long value);
    void writeInt(String key, int value);
    void writeFloat(String key, float value);
    
    // reading
    long readLong(String key);
    int readInt(String key);
    float readFloat(String key);
private:
    int hash(String key);
    bool shouldDebug;
    void debugln(String s);
    void debug(String s);
};