#ifndef MOTORSHANDLER_HPP_
#define MOTORSHANDLER_HPP_

// https://github.com/atmelino/Arduino/tree/master/libraries/PWM
#include "Motor.hpp"

#define AMOUNT_MOTORS 4

class MotorsHandler {

public:

    MotorsHandler(int, int, int, int, int, int, int, int);
    void initMotor(class Motor&);
    void reset();

    void refreshAll();
    bool checkFBVoltage();

public :

    class Motor motors[AMOUNT_MOTORS];

private:

    int pins[AMOUNT_MOTORS] = { 0 };
    int fbpins[AMOUNT_MOTORS] = { 0 };

};

#endif