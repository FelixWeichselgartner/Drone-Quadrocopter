#include "Motor.hpp"

// https://github.com/atmelino/Arduino/tree/master/libraries/PWM
#include "PWM.h"

Motor::Motor() {
    this->pin = this->D = this->f = 0;
}

Motor::Motor(int pin, int D, int f) {
    this->pin = pin;
    this->D = D;
    this->f = f;
}

void Motor::refresh() {
    int output = map(this->D, 0, 1000, 0, 255);
    pwmWrite(this->pin, output);
}