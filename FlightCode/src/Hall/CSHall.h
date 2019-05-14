#ifndef _CSHALL_H
#define _CSHALL_H

class CSHall {
public:
    CSHall(void);
    void config(int p);

    int getCurrentCount(void);
    void increment(void); // Use as callback
    void clearCount(void);
private:
    int pin;
    int count;
};

#endif 