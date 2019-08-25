#include "Arduino.h"
#include "MotorsHandler.hpp"

/**
 * @brief  gets all motors pins and handles them in a class.
 * @note   frequency is redundant at the moment.
 * @param  pin_m1: motor/pwm pins.
 * @param  pin_m2: 
 * @param  pin_m3: 
 * @param  pin_m4: 
 * @param  frequency: 
 * @param  fb_m1: feedback pins for actual motor voltage.
 * @param  fb_m2: 
 * @param  fb_m3: 
 * @param  fb_m4: 
 * @retval 
 */
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

/**
 * @brief  initialises the motor pin.
 * @note   
 * @param  m: motor object
 * @retval None
 */
void MotorsHandler::initMotor(class Motor& m) {
    pinMode(m.getPin(), OUTPUT);
}

/**
 * @brief  creates the motors objects.
 * @note   inits all motor pins.
 * @retval None
 */
void MotorsHandler::reset() {
    for (int i = 0; i < AMOUNT_MOTORS; i++) {
        motors[i] = Motor(this->pins[i], 0, this->frequency, this->fbpins[i]);
        initMotor(motors[i]);
    }
}

/**
 * @brief  adjusts the duty cycle for all motor pins.
 * @note   
 * @retval None
 */
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