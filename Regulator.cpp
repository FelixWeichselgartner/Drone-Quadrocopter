#include "Regulator.hpp"

 /**
  * @brief  constructor for regulator class.
  * @note   
  * @param  min: the minimum value of the regulator.
  * @param  max: the maximum value of the regulator.
  * @retval 
  */
Regulator::Regulator(float min, float max) {
    this->min = min;
    this->max = max;
}