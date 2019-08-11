#include "Debug.hpp"
#include "Arduino.h"
#include "LED.hpp"
#include "drone_config.h"

Debug::Debug() { 

}

bool Debug::motors() { 

}

bool Debug::led() { 
    class LED led(LED_1);
    for (int i = 0; i < 10; i++) {
        led.on();
        delay(500);
        led.off();
        delay(500);
    };
}

bool Debug::lipo() { 

}

bool Debug::accelerometer() { 

}

