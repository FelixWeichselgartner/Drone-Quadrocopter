#include "drone_config.h"
#include "Debug.hpp"
#include "MotorsHandler.hpp"

class Debug debug;

class MotorsHandler motorshandler(
    MOTOR_1_PWM,
    MOTOR_2_PWM,
    MOTOR_3_PWM,
    MOTOR_4_PWM,
    10,
    MOTOR_1_FB,
    MOTOR_2_FB,
    MOTOR_3_FB,
    MOTOR_4_FB
);

void setup() {
  
}

void loop() {
  debug.led();
  debug.motors(motorshandler);
}
