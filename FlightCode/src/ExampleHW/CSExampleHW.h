

class CSExampleHW {
public:
    // Initializers: for use in `setup` function
    void init(int p);
    
    // Accessors: for use everywhere else
    float getData();
private:
    // Any private, hardware-specific variables that need to be managed
    int pin;
}