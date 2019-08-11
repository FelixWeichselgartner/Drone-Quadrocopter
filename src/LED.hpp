#ifndef LED_HPP_
#define LED_HPP_

class LED {

public:

    LED(int);

    inline bool getState() { return this->state; }
    inline void setState(bool state) { this->state = state; }

    inline void setPin(int pin) { this->pin = pin; }

    void on();
    void off();

private:

    bool state;
    int pin;

};

#endif