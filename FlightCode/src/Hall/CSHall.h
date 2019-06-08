#ifndef _CSHALL_H
#define _CSHALL_H

class CSHall {
public:
    CSHall(void);
    void config(int p);

    float getRpm(void);
private:
    int pin;
};

#endif 