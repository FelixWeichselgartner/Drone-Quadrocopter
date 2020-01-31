#include "Arduino.h"
#include "Motor.hpp"


/**
 * @brief  default constructor (not used)
 * @note   
 * @retval 
 */
Motor::Motor() {
    this->pin = this->D = this->fbpin = 0;
}

/**
 * @brief  constructor.
 * @note   saves pin, duty cycle and feedback pin.
 * @param  pin: 
 * @param  D: 
 * @param  fbpin: 
 * @retval 
 */
Motor::Motor(int pin, int D, int fbpin) {
    this->pin = pin;
    this->D = D;
    this->fbpin = fbpin;
}

/**
 * @brief  reads feedback voltage from feedback pin.
 * @note   in milli volts.
 * @retval 
 */
int Motor::getFBVoltage() {
    return (long long) analogRead(this->fbpin) * 5000 / 1024;
}

/**
 * @brief  maps duty cycle from e.g. 0-255 to 0-1023
 * @note   
 * @param  x: number to map
 * @param  in_min: old min
 * @param  in_max: old max
 * @param  out_min: new min
 * @param  out_max: new max
 * @retval new x
 */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief  sets the duty cycle of a motor.
 * @note   maps from 0-1000 to 0-255. -> you lose resolution here.
 * @retval None
 */
void Motor::refresh() {
    int output = map(this->D, 0, 1000, 0, 255);
    analogWrite(this->pin, output);
}