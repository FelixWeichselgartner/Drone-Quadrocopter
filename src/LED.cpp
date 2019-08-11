#include "Arduino.h"
#include "LED.hpp"

LED::LED(int pin) { 
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void LED::on() { 
    digitalWrite(pin, HIGH);
}

void LED::off() { 
    digitalWrite(pin, LOW);
}

