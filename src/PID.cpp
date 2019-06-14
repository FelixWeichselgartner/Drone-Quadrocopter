#include "PID.hpp"

 /**
  * @brief  constructor for PID class.
  * @note   
  * @param  min: the minimum output of the PID regulator.
  * @param  max: the maximum output of the PID regulator.
  * @param  K_P: the factor for the proportional part.
  * @param  K_I: the factor for the integral part.
  * @param  K_D: the factor for the differential part.
  * @param  dt:  the time interval in which the tick function is executed.
  * @retval None
  */
PID::PID(
    float min, 
    float max, 
    float K_P, 
    float K_I, 
    float K_D, 
    float dt
    ): Regulator(min, max) {
    
    this->K_P = K_P;
    this->K_I = K_I;
    this->K_D = K_D;
    this->dt = dt;
    this->integrate = 0;
}

 /**
  * @brief  one iteration of the regulator loop.
  * @note   execute tick every dt seconds.
  * @param  s: the value you want to set
  * @param  m: the current value
  * @retval the regulator output
  */
float PID::tick(float s, float m) {
    float e = s - m;

    this->integrate += e * this->dt;
    float devrivate = (e - this->prev_e) / this->dt;

    this->P = this->K_P * e;
    this->I = this->K_I * this->integrate;
    this->D = this->K_D * devrivate;

    float output = this->P + this->I + this->D;

    if (output > this->getMax()) {
        output = this->getMax();
    } else if (output < this->getMin()) {
        output = this->getMin();
    }

    this->prev_e = e;

    return output;
}