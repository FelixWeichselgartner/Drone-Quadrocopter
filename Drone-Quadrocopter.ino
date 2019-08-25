/*
Copyright (c) 2019 Felix Weichselgartner
All rights are reserved.
*/

#include "src/MotorsHandler.hpp"
#include "src/PID.hpp"
#include "src/LiPo.hpp"
using namespace LiPo;
#include "src/MPUHandler.hpp"
#include "src/drone_config.h"

// duty cycle base for compensating earth gravitation.
const int mV_base = 1300;
const int mV_motorPower = 3700;
int d_base = 300;

int updateDBase(int mV_lipo) {
    d_base = mV_base * mV_motorPower / mV_lipo;
}

// PWM-Pins, Switching-Frequncy = 50kHz, feedback pins.
/*
class MotorsHandler motorshandler(
    MOTOR_1_PWM,
    MOTOR_2_PWM,
    MOTOR_3_PWM,
    MOTOR_4_PWM,
    50000,
    MOTOR_1_FB,
    MOTOR_2_FB,
    MOTOR_3_FB,
    MOTOR_4_FB
);
*/

// pid factors and pid time interval.
float K_P = 1.4, K_I = 0.2, K_D = 0.75, dt = 0.001;
// wanted angles.
float wantedAngleX = 0, wantedAngleY = 0;
// pid regulator for x and y axis.
class PID pid_x(0, 1000, K_P, K_I, K_D, dt);
class PID pid_y(0, 1000, K_P, K_I, K_D, dt);

// LiPo battery.
class LiPo lipo(3300, 10);

// handler for MPU9250.
class MPUHandler mpuhandler;

void setup() {
    pinMode(3, OUTPUT);
}

void work() {
    int lipo_mV, lipo_per;
    lipo.getState(analogRead(LIPO_FB), lipo_mV, lipo_per);
    
    updateDBase(lipo_mV);

    float angle_x, angle_y;
    mpuhandler.calculateAngles(angle_x, angle_y);
    
    float d_x = (int)pid_x.tick(wantedAngleX, angle_x);
    float d_y = (int)pid_y.tick(wantedAngleY, angle_y);
    /*
    motorshandler.motors[0].setDutyCycle(d_base + d_x);
    motorshandler.motors[1].setDutyCycle(d_base + d_y);
    motorshandler.motors[2].setDutyCycle(d_base - d_x);
    motorshandler.motors[3].setDutyCycle(d_base - d_y);
    
    motorshandler.refreshAll();*/
}

#include "src/Debug.hpp"

void debug() {
    class Debug d;
    d.led();
    //d.motors(motorshandler);
    
    while(1) {
      digitalWrite(3, HIGH);
      delay(300);
      digitalWrite(3, LOW);
      delay(300);
    }
}

void loop() {
    //work();
    debug();
}
