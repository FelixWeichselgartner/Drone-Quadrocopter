#ifndef MOTOR_HPP_
#define MOTOR_HPP_

class Motor {

public:

    Motor();
    Motor(int, int, int, int);
    
    // get the pwm pin the motor control pin is connected to.
    inline int getPin() const { return this->pin; }
    // set the pwm pin the motor control pin is connected to.
    inline void setPin(int pin) { this->pin = pin; }
    // get the current duty cycle of the motor.
    inline int getDutyCycle() const { return this->D; }
    // set the current duty cycle of the motor.
    inline void setDutyCycle(int D) { this->D = D; }
    // get the current switching (pwm) frequency of the motor.
    inline int getSwitchFreq() const { return this->f; }
    // set the current switching (pwm) frequency of the motor.
    inline void setSwitchFreq(int f) { this->f = f; }
    // get analog feedback pin.
    inline int getFBPin() const { return this->fbpin; }
    // set analog feedback pin.
    inline void setFBPin(int pin) { this->fbpin = fbpin; }

    // get voltage in mV from feedback pin.
    int getFBVoltage();

    void refresh();

private:

    // pwm pin.
    int pin;
    // duty cycle in 10 * % (e.g. 1000 = 100%).
    int D;
    // switching (pwm) frequency.
    int f;
    // analog feedback pin.
    int fbpin;

};

#endif