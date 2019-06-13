#ifndef REGULATOR_HPP_
#define REGULATOR_HPP_

class Regulator {

public:

    Regulator(float min, float max);

    virtual float tick() = 0;

    // returns the minimum value.
    inline float getMin() { return this->min; }
    // sets the minimum value.
    inline void setMin(float min) { this->min = min; }
    // returns the maximum value.
    inline float getMax() { return this->max; }
    // sets the maximum value.
    inline void setMax(float max) { this->max = max; }

private:

    float min, max;

};

#endif