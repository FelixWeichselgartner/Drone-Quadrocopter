#include "PID.hpp"

PID::PID(
    float min, 
    float max, 
    float K_P, 
    float K_I, 
    float K_D, 
    float dt
    ): Regulator(min, max) {
    this->dt = dt;
    this->K_P = K_P;
    this->K_I = K_I;
    this->K_D = K_D;
    this->integrate = 0;
}

float PID::tick(float s, float m) {
    float e = s - m;
    this->P = this->K_P * e;
    this->integrate += e * this->dt;
    
}