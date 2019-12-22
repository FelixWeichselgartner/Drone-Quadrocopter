#include "Arduino.h"
#include "LED.hpp"

/**
 * @brief  led constructor.
 * @note   saves the pin and current state.
 * @param  pin: led pin
 * @retval 
 */
LED::LED(int pin) { 
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

/**
 * @brief  sets output HIGH and saves state.
 * @note   
 * @retval None
 */
void LED::on() { 
    this->state = true;
    digitalWrite(pin, HIGH);
}

/**
 * @brief  sets output LOW and saves state.
 * @note   
 * @retval None
 */
void LED::off() { 
    this->state = false;
    digitalWrite(pin, LOW);
}

