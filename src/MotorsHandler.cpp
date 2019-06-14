#include "MotorsHandler.hpp"

MotorsHandler::MotorsHandler(
    int pin_m1, 
    int pin_m2, 
    int pin_m3, 
    int pin_m4, 
    int frequency
    ) {
    
    this->pins[0] = pin_m1;
    this->pins[1] = pin_m2;
    this->pins[2] = pin_m3;
    this->pins[3] = pin_m4;
    this->frequency = frequency;

    reset();
}

void MotorsHandler::initMotor(class Motor& m) {
    if (SetPinFrequencySafe(m.getPin(), m.getSwitchFreq())) {
        pinMode(m.getPin(), OUTPUT);
        digitalWrite(m.getPin(), HIGH);
    }
}

void MotorsHandler::reset() {
    InitTimersSafe();

    for (int i = 0; i < AMOUNT_MOTORS; i++) {
        motors[i] = Motor(this->pins[i], 0, this->frequency);
        initMotor(motors[i]);
    }
}

void MotorsHandler::refreshAll() {
    for (int i = 0; i < AMOUNT_MOTORS; i++) {
        motors[i].refresh();
    }
}