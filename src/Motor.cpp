#include "Motor.hpp"

// https://github.com/atmelino/Arduino/tree/master/libraries/PWM
#include "PWM.h"

Motor::Motor() {
    this->pin = this->D = this->f = this->fbpin = 0;
}

Motor::Motor(int pin, int D, int f, int fbpin) {
    this->pin = pin;
    this->D = D;
    this->f = f;
    this->fbpin = fbpin;
}

int Motor::getFBVoltage() {
    return analogRead(this->fbpin) * 3300 / 1024;
}

void Motor::refresh() {
    int output = map(this->D, 0, 1000, 0, 255);
    pwmWrite(this->pin, output);
}