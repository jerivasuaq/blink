#include "LEDBlinker.h"

LEDBlinker::LEDBlinker(int pin, unsigned long interval)
    : pin(pin), interval(interval), lastToggle(0), state(false) {}

void LEDBlinker::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    lastToggle = millis();
    state = false;
}

void LEDBlinker::update() {
    unsigned long now = millis();
    if (now - lastToggle >= interval) {
        state = !state;
        digitalWrite(pin, state ? HIGH : LOW);
        lastToggle = now;
    }
}

void LEDBlinker::setInterval(unsigned long ms) {
    interval = ms;
}
