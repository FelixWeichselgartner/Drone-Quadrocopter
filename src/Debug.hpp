#ifndef DEBUG_HPP_
#define DEBUG_HPP_

class MotorsHandler;

class Debug {

public:

    Debug();

    inline int getError() { return this->error; }
    inline void setError(int error) { this->error = error; }

    bool motors(MotorsHandler&);
    bool led();
    bool lipo();
    bool accelerometer();

private:

    int error;

};

#endif