// Test CSCoreData class

#include <EEPROM.h>
#include <stdint.h>
#include "CSCoreData.h"

CSCoreData coreData;

// Assertions
int pass = 0;
int fail = 0;
bool CSAssert(bool b) {
    if (b) {pass++; Serial.println("Test pass");}
    else   {fail++; Serial.println("Test fail");}
    
    return b;
}

void setup() {
    Serial.begin(9600); delay(500);
    
    coreData.config();
    coreData.debugMode(true);
    
    coreData.deleteAll(); // Wipe it clean for testing!
    
    // As a hash table? Sure! 
    // Size? 20 longs = 80 bytes (check that)
    long l = 123456;
    coreData.writeLong("long", l);
    Serial.println("Saved " + String(l));
    
    int i = 20000;
    coreData.writeInt("int", i);
    Serial.println("Saved " + String(i));
    
    float f = 300.75;
    coreData.writeFloat("float", f);
    Serial.println("Saved " + String(f));
    
    // Read values back and print them!
    Serial.println("\n\n");
    long l2 = coreData.readLong("long");
    Serial.println("Read " + String(l2));
    
    int i2 = coreData.readInt("int");
    Serial.println("Read " + String(i2));
    
    float f2 = coreData.readFloat("float");
    Serial.println("Read " + String(f2));
    
    
    // Make assertions
    CSAssert(l == l2);
    CSAssert(i == i2);
    CSAssert(f == f2);
    Serial.println("\n\nResults:");
    Serial.println("Pass: " + String(pass));
    Serial.println("Fail: " + String(fail));
    
    if (fail != 0) {
        Serial.println("\nWarning: Some test cases failed. Try again.");
    }
}

void loop() {
    // Nothing
}