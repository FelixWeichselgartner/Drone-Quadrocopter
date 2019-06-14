#include "MotorsHandler.hpp"

MotorsHandler::MotorsHandler(
    int pin_m1, 
    int pin_m2, 
    int pin_m3, 
    int pin_m4, 
    int frequency,
    int fb_m1,
    int fb_m2,
    int fb_m3,
    int fb_m4
    ) {
    
    this->pins[0] = pin_m1;
    this->pins[1] = pin_m2;
    this->pins[2] = pin_m3;
    this->pins[3] = pin_m4;
    this->frequency = frequency;
    this->fbpins[0] = fb_m1;
    this->fbpins[1] = fb_m2;
    this->fbpins[2] = fb_m3;
    this->fbpins[3] = fb_m4;

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
        motors[i] = Motor(this->pins[i], 0, this->frequency, this->fbpins[i]);
        initMotor(motors[i]);
    }
}

void MotorsHandler::refreshAll() {
    for (int i = 0; i < AMOUNT_MOTORS; i++) {
        motors[i].refresh();
    }
}

bool MotorsHandler::checkFBVoltage() {
    for (int i = 0; i < AMOUNT_MOTORS; i++) {
        if (motors[i].getFBVoltage() > 930) {
            return true;
        }
    }
}