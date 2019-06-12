#ifndef REGULATOR_HPP_
#define REGULATOR_HPP_

class Regulator {

public:

    Regulator(float min, float max);

    virtual float tick() = 0;

    float getMin() { return this->min; }
    void setMin(float min) { this->min = min; }
    float getMax() { return this->max; }
    void setMax(float max) { this->max = max; }

private:

    float min, max;

};

#endif