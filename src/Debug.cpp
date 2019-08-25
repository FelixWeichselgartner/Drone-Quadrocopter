#include "Debug.hpp"
#include "Arduino.h"
#include "LED.hpp"
#include "drone_config.h"
#include "MotorsHandler.hpp"

Debug::Debug() { 

}

/**
 * @brief  sets some example duty cycles to check if motors would work.
 * @note   
 * @param  motorshandler: 
 * @retval 
 */
bool Debug::motors(MotorsHandler& motorshandler) { 
    motorshandler.motors[0].setDutyCycle(512);
    motorshandler.motors[1].setDutyCycle(1000);
    motorshandler.motors[2].setDutyCycle(300);
    motorshandler.motors[3].setDutyCycle(200);
    motorshandler.refreshAll();
}

/**
 * @brief  tests the led.
 * @note   
 * @retval 
 */
bool Debug::led() { 
    class LED led(LED_1);
    for (int i = 0; i < 10; i++) {
    //while(1) {
        led.on();
        delay(500);
        led.off();
        delay(500);
    };
    led.on();
}

bool Debug::lipo() { 

}

bool Debug::accelerometer() { 

}

