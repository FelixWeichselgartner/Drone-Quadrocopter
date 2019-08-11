#include "MPUHandler.hpp"
#include "math.h"

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

void getZRotationMatrix(float *R, angleDegree) {
    float angle = angleDegree / 180 * M_PI;
    float Rs[3][3] = {
        cos(angle), -sin(angle), 0,
        sin(angle), cos(angle), 0,
        0, 0, 1
    };

    if (R != NULL) {
        delete[] R;
    }
    R = new float[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = Rs[i][j];
        }
    }
}

// M x P * P x N = M x N
void matmul(float *mat1,
            float *mat2,
            float *res,
            int m, int p, int n) {

    if (res != NULL) {
        delete[] res;
    }
    res = new float[m][n];

    for (int i = 0; i < m; i++) { 
        for (int j = 0; j < p; j++) { 
            res[i][j] = 0; 
            for (int k = 0; k < n; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j]; 
            }
        } 
    } 
} 

void vektorToAngle(float* v, float& ax, float& ay) {
    ax = atan(v[0]/(sqrt(v[1]*v[1] + v[2]*v[2])));
    ay = atan(v[1]/(sqrt(v[0]*v[0] + v[2]*v[2])));
}

void MPUHandler::calculateAngles(float &ax, float &ay) {
    float *R;
    float acc[3], acc_R;

    mpu.readSensor();
    acc[0] = mpu.getAccelX_mss();
    acc[1] = mpu.getAccelY_mss();
    acc[2] = mpu.getAccelZ_mss();

    getZRotationMatrix(R, 45);
    matmul(acc, R, acc_R, 3, 3, 1);
    vektorToAngle(acc_R, ax, ay);
}