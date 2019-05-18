#ifndef _CSHALL_H
#define _CSHALL_H

class CSHall {
public:
    CSHall(void);
    void config(int p);

    int getCurrentCount(void);
    static void increment(void); // Use as callback
    void clearCount(void);
private:
    int pin;
};

#endif 