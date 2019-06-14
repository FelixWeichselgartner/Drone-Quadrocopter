#include "MPUHandler.hpp"

MPUHandler::MPUHandler() { 
    mpu = MPU9250(Wire, 0x68);
    reset();
}

void MPUHandler::reset() {
    int status = mpu.begin();
    if (status < 0) {
        /*
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
        */
        while(1) {}
    }
}

void MPUHandler::calculateAngles(float &ax, float &ay) {
    float x, y, z;
    float ax, ay;
    mpu.readSensor();
    x = mpu.getAccelX_mss();
    y = mpu.getAccelY_mss();
    z = mpu.getAccelZ_mss();
    ax = atan(x/(sqrt(y*y + z*z)));
    ay = atan(y/(sqrt(x*x + z*z)));
}