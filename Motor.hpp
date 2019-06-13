#ifndef MOTOR_HPP_
#define MOTOR_HPP_

class Motor {

public:

    Motor(int, int, int);

    // get the pwm pin the motor control pin is connected to.
    inline int getPin() { return this->pin; }
    // set the pwm pin the motor control pin is connected to.
    inline void setPin(int pin) { this->pin = pin; }
    // get the current duty cycle of the motor.
    inline int getDutyCycle() { return this->D; }
    // set the current duty cycle of the motor.
    inline void setDutyCycle(int D) { this->D = D; }
    // get the current switching (pwm) frequency of the motor.
    inline int getSwitchFreq() { return this->f; }
    // set the current switching (pwm) frequency of the motor.
    inline void setSwitchFreq(int f) { this->f = f; }

    void refresh();

private:

    // pwm pin.
    int pin;
    // duty cycle.
    int D;
    // switching (pwm) frequency.
    int f;

};

#endif