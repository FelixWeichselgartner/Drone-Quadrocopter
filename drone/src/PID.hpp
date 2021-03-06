#ifndef PID_HPP_
#define PID_HPP_

#include "Regulator.hpp"

class PID: public Regulator {

public:

    PID(float, float, float, float, float);

    float tick(float, float, unsigned int);

private:

    float K_P, K_I, K_D;
    float P, I, D;
    float I_Max;
    float integrate;
    float ys, prev_e;

};

#endif