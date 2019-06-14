/*
Copyright (c) 2019 Felix Weichselgartner

All rights are reserved.
*/

#include "src/MotorsHandler.hpp"
#include "src/PID.hpp"
#include "src/LiPo.hpp"
#include "src/MPUHandler.hpp"

// duty cycle base for compensating earth gravitation.
int d_base = 300;
// PWM-Pins: 3, 5, 6, 9; Switching-Frequncy = 50kHz
class MotorsHandler motorshandler(3, 5, 6, 9, 50000);

// pid factors and pid time interval.
float K_P = 1, K_I = 1, K_D = 1, dt = 0.001;
// wanted angles.
float wantedAngleX = 0, wantedAngleY = 0;
// pid regulator for x and y axis.
class PID pid_x(0, 1000, K_P, K_I, K_D, dt);
class PID pid_y(0, 1000, K_P, K_I, K_D, dt);

// Pin to read in battery voltage.
int pin_lipo = A6;
// LiPo battery.
class LiPo lipo(3300, 10);

// handler for MPU9250.
class MPUHandler mpuhandler;

void setup() {

}

void loop() {
    float angle_x, angle_y;
    mpuhandler.calculateAngles(angle_x, angle_y);
    
    float d_x = (int)pid_x(wantedAngleX, angle_x);
    float d_y = (int)pid_y(wantedAngleY, angle_y);
    
    motorshandler.m[0].setD(d_base + d_x);
    motorshandler.m[1].setD(d_base + d_y);
    motorshandler.m[2].setD(d_base - d_x);
    motorshandler.m[3].setD(d_base - d_y);
    
    motorshandler.refreshAll();
}
