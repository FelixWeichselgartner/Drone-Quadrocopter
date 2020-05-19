/*
Copyright (c) 2020 Felix Weichselgartner
All rights are reserved.
*/

#include "src/MotorsHandler.hpp"
#include "src/PID.hpp"
#include "src/LED.hpp"
#include "src/LiPo.hpp"
#include "MPU9250.h"
#include "src/MPUHandler.hpp"
#include "src/drone_config.h"
#include "src/debug.h"

// duty cycle base for compensating earth gravitation.
const int mV_base = 1300;
const int mV_motorPower = 3700;
int d_base = 500;

int updateDBase(int mV_lipo) {
    d_base = (long long) mV_base * mV_motorPower / mV_lipo;
}

// PWM-Pins, feedback pins.
class MotorsHandler motorshandler(
    MOTOR_1_PWM,
    MOTOR_2_PWM,
    MOTOR_3_PWM,
    MOTOR_4_PWM,
    MOTOR_1_FB,
    MOTOR_2_FB,
    MOTOR_3_FB,
    MOTOR_4_FB
);

// pid factors and pid time interval.
int factor = 200;
float K_P = 1.4 * factor, K_I = 0.2 * factor, K_D = 0.75 * factor;
// wanted angles.
float wantedAngleX = 0, wantedAngleY = 0;

// pid regulator for x and y axis.
unsigned long start_time;
class PID pid_x(0, 1000, K_P, K_I, K_D);
class PID pid_y(0, 1000, K_P, K_I, K_D);

// LED.
class LED led_1(LED_1);

// LiPo battery.
class LiPo lipo(3300, 10);

// somehow MPU9250 class only works as a global variable.
MPU9250 mpu = MPU9250(Wire, 0x68);

void setup() {
    led_1.on();

    Serial.begin(9600);
    while(!Serial) {
        led_1.off();
    }

    led_1.on();
}

void work(MPUHandler *mpuhandler) {
    int lipo_mV, lipo_per;
    bool lipo_state;
    lipo_mV = lipo.getCurrentVoltage();
    lipo_per = lipo.getPercentageLoaded();
    lipo_state = lipo.getState();
    //updateDBase(lipo_mV);

    float angle_x, angle_y;
    mpuhandler->calculateAngles(angle_x, angle_y);

    #if DEBUG
    /*Serial.print("angle x, y: ");
    Serial.print(angle_x);
    Serial.print(" ");
    Serial.print(angle_y);
    Serial.print("\n");*/
    #endif
    
    unsigned int dt = millis() - start_time;
    float d_x = pid_x.tick(wantedAngleX, angle_x, dt) * 2.5;
    float d_y = pid_y.tick(wantedAngleY, angle_y, dt) * 2.5;
    start_time = millis();


    /*Serial.print("wanted angle x: ");
    Serial.println(angle_x);
    Serial.print("d_x = ");
    Serial.println(d_x);*/
    /*
    Serial.print("d x, y: ");

    Serial.print(" ");
    Serial.print(d_y);
    Serial.print("\n");*/
    //delay(500);

    Serial.print(d_base + d_x);
    Serial.print(" ");
    Serial.print(d_base + d_y);
    Serial.print(" ");
    Serial.print(d_base - d_x);
    Serial.print(" ");
    Serial.println(d_base - d_y);

    
    
    //motorshandler.motors[0].setDutyCycle(d_base - d_x); // wrong way around
    //motorshandler.motors[1].setDutyCycle(d_base - d_y);
    //motorshandler.motors[2].setDutyCycle(d_base + d_x); // minus was false
    //motorshandler.motors[3].setDutyCycle(d_base + d_y); // minus was false
    
    motorshandler.refreshAll();
}

void loop() {
    start_time = millis();
    // handler for MPU9250.
    class MPUHandler mpuhandler(&mpu);
    while(1) {
        work(&mpuhandler);
    }
}
