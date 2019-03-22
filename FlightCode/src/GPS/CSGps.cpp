// Implementatin file


#include "CSGps.h"


CSGps::CSGps(SoftwareSerial* ss) {
    serial = ss;
    satellites = 0;
    altitude = 0;
    fix = false;
    
    lat = 0;
    lon = 0;
    time = 0;
    
    hour = 0, minute = 0, seconds = 0, year = 0, month = 0, day = 0;
    
    shouldDebug = false;
}

void CSGps::update() {
    // Read character, store in string
    if (serial->available()) {
        char c = serial->read(); // Works
        if (c == '$') { // Start of packet. Clear string.
            // cout << "\tupdate: start of packet" << endl;
            temp = c; // Available in arduino?
            packetReceived = false;
        } else if (c == '\r') { // End of packet. Parse. DO NOT CLEAR YET.
            parsePacket();
            packetReceived = true;
        } else { // Simple append
            packetReceived = false;
            temp += c;
        }
    }
    
}

void CSGps::debugln(String s) {
    // If debug, print string to Serial
    if (shouldDebug) {
        Serial.println("CSGps: " + s);
    }
}

bool CSGps::available() {
    return serial->available();
}

char CSGps::read() {
    return serial->read();
}

void CSGps::begin(int baud) {
    serial->begin(baud);
}





// $GPGGA,033109.297,3325.2589,N,11155.7849,W,1,09,0.88,394.6,M,-26.5,M,,*55
void CSGps::parsePacket() {
    // Serial.println("CSGPS.parsePacket() on temp: " + temp);
    // Break packet into components. Update vars if certain packet type
    // Use atof instead of atoi (doubles instead of ints)
    // Operate on temp string
    // vector<string> strings;
    CSVector stringVector;
    
    String s = "";
    for (int i = 0; i < temp.length(); i++) {
        char c = temp.charAt(i);
        // cout << "parsePacket: Read " << c << endl;
        if (c == ',' || c == '\r') { // Push current string onto list
            stringVector.push_back(s);
            // Serial.println("\tFound: " + s);
            s = ""; // Reset current string
        } else if (c == '$') { // Don't push on the first bit
            // Skip
        } else {
            s += c; // Can push characters onto it
        }
    }
    
    // Print all detected strings
    // Serial.println("Print all detected strings: ");
    // for (int i = 0; i < stringVector.count; i++) {
    //     Serial.println("\t" + stringVector.at(i));
    // }
    
    // Here is where you'd choose the packet type:
    // if (strings[0] == "GPGGA") {
    if (stringVector.at(0) == "GPGGA") {
        // cout << "^^This was a GPGGA packet!" << endl;
        // lat = 
        if (stringVector.at(6) == "1") { // Only update if locked
            // Serial.println("GPGGA locked!");
            // Serial.println("\tlat: " + stringVector.at(2));
            // Serial.println("\tlon: " + stringVector.at(4));
            lat = atof(stringVector.at(2).c_str());
            lon = atof(stringVector.at(4).c_str());
            time = atof(stringVector.at(1).c_str());
            altitude = atof(stringVector.at(9).c_str());
            satellites = atoi(stringVector.at(7).c_str());
            
            packetReceived = true;
        }
    } else {
        packetReceived = false; // Ignore all other types
    }
    
    stringVector.destroy();
}






// CSVector functions
CSVector::CSVector() {
    // Init head
    head = NULL;
    count = 0;
}

void CSVector::push_back(String s) {
    StringNode_t* newNode = new StringNode_t;
    newNode->s = s;
    newNode->next = NULL;
    count++;
    
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    // Walk the tree
    StringNode_t* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Set
    temp->next = newNode;
}

String CSVector::at(int i) {
    StringNode_t* temp = head;
    for (int j = 0; j < i; j++) {
        temp = temp->next;
    }
    
    return temp->s;
}

void CSVector::destroy() {
    // Delete all nodes
    
    StringNode_t* temp = head;
    StringNode_t* prev;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
        delete prev;
    }
    delete temp;
    
    head = NULL;
}

void CSVector::printAll() {
    StringNode_t* temp = head;
    if (head == NULL) {
        return;
    }
    
    Serial.println("Start Print all");
    for (int i = 0; i < count; i++) {
        Serial.println(String(i) + ": " + temp->s);
        temp = temp->next;
    }
    // int i = 0;
    // while (temp->next != NULL) {
    //     Serial.println(String(i) + ": " + temp->s);
    //     if (temp->next == NULL || temp == NULL) {
    //         break;
    //     }
    //     temp = temp->next;
    //     i++;
    // }
    // Serial.println(String(i) + ": " + temp->s);
}