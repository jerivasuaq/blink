#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include <Arduino.h>

class LEDBlinker {
private:
    int pin;
    unsigned long interval;
    unsigned long lastToggle;
    bool state;
public:
    LEDBlinker(int pin, unsigned long interval = 500);
    void begin();
    void update();
    void setInterval(unsigned long ms);
};

#endif // LED_BLINKER_H
