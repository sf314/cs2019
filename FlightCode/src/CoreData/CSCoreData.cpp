// CSCoreData implementation file

#include "CSCoreData.h"

CSCoreData::CSCoreData() {
    // Nothing?
    shouldDebug = false;
}

void CSCoreData::config() {
    // Nothing
    shouldDebug = false;
}

void CSCoreData::debugMode(bool b) {
    shouldDebug = b;
}

void CSCoreData::deleteAll() {
    // Write zeroes to EEPROM (up to max 512 bytes)
    for (int i = 0; i < 512; i++) {
        EEPROM.write(i, 0);
    }
}

void CSCoreData::writeLong(String key, long value) {
    // 4 bytes. MSbyte at first index
    int hashVal = hash(key);
    
    // Disassemble long into 4 bytes
    char arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = (value >> (32 - (i + 1) * 8)) & 0xFF;
    }
    
    // Store bytes in EEPROM
    for (int i = 0; i < 4; i++) {
        EEPROM.write(hashVal + i, arr[i]);
    }
    
    debugln("CSCoreData: write " + String(value) + " @ " + String(hashVal) + " for key " + key);
}

void CSCoreData::writeInt(String key, int value) {
    // 2 bytes! MSbyte first.
    int hashVal = hash(key);
    
    // Disassemble into 2 bytes
    char upper = (value >> 8) & 0x00FF;
    char lower = value & 0xFF;
    
    // Store bytes into EEPROM
    EEPROM.write(hashVal, upper);
    EEPROM.write(hashVal + 1, lower);
    
    debugln("CSCoreData: write " + String(value) + " @ " + String(hashVal) + " for key " + key);
}

void CSCoreData::writeFloat(String key, float value) {
    // float is 4 bytes, so just use the long function!
    long l = 0;
    float* pointerToFloat = &value;
    long* pointerAsLong = (long*)pointerToFloat;
    l = l | *pointerAsLong;
    writeLong(key, l); // takes care of logging
}

long CSCoreData::readLong(String key) {
    // 4 bytes, MSbyte at first index
    int hashVal = hash(key);
    
    // Retrieve 4 bytes from EEPROM
    char arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = EEPROM.read(hashVal + i);
    }
    
    // Reassemble bytes into long
    long temp = 0;
    for (int i = 0; i < 4; i++) {
        temp |= (arr[i] << (32 - (i + 1) * 8));
    }
    
    debugln("CSCoreData: read " + String(temp) + " @ " + String(hashVal) + " for key " + key);
    
    return temp;
}

int CSCoreData::readInt(String key) {
    // 2 bytes only!
    int hashVal = hash(key);
    
    // Retrieve bytes from EEPROM
    char upper = EEPROM.read(hashVal);
    char lower = EEPROM.read(hashVal + 1);
    
    // Reassemble int
    int temp = 0;
    temp |= upper << 8;
    temp |= lower;
    
    debugln("CSCoreData: read " + String(temp) + " @ " + String(hashVal) + " for key " + key);
    
    return temp; // wow
}

float CSCoreData::readFloat(String key) {
    // Float is 4 bytes, so just use long!
    long l = readLong(key); // takes care of logging
    
    long* ptrToLong = &l;
    float* ptrToFloat = (float*)ptrToLong;
    float f = *ptrToFloat;
    
    return f;
}

int CSCoreData::hash(String key) {
    // Assume max eeprom of 512 bytes, therefore 128 unique indexes
    // Every 4 bytes, up to 508
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += (int)key[i];
    }
    
    int result = (sum % 128) * 4;
    // Perform checks?
    
    return result;
}

void CSCoreData::debugln(String s) {
    if (shouldDebug) {
        Serial.println(s);
    }
}
void CSCoreData::debug(String s) {
    if (shouldDebug) {
        Serial.print(s);
    }
}