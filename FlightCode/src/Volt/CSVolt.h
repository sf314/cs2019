#ifndef _CSVOLT_H
#define _CSVOLT_H


class CSVolt {
public:
    // Constructor
    CSVolt(void); 
    void config(int p);
    void setSampleSize(int newSize);

    // Data
    float read();

private:
    int pin;
    int sampleSize;
};

#endif 