#ifndef MPUHANDLER_HPP_
#define MPUHANDLER_HPP_

// https://github.com/bolderflight/MPU9250
#include "MPU9250.h"

class MPUHandler
{

public:
    MPUHandler();
    void reset();

    void calculateAngles(float &, float &);

private:
    MPU9250 mpu = MPU9250(Wire, 0x68);
    float R[3][3];
};

#endif