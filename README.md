## Drone-Quadrocopter

An Arduino based Quadrocopter with switch-mode power, rfm95-LoRa-radio and mpu950-accelerometer.

Remote with PS2-Controller and rfm95-LoRa-radio.

Here the schematics for the hardware:

Drone:

![img](https://github.com/FelixWeichselgartner/Drone-Quadrocopter/blob/master/schematics/Drone-Schematic.png)

Remote:

![img](https://github.com/FelixWeichselgartner/Drone-Quadrocopter/blob/master/schematics/Remote-Schematic.png)

*****************************************************************************************

### Copyright (c) 2019 Felix Weichselgartner

All rights are reserved.

If you have questions or improvements pls contact me:

info@felix-weichselgartner.de

*****************************************************************************************

### File assosiation:

* .asc -> LTSpice (https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html)
* .fzz -> Fritzing (http://fritzing.org/home/)
* .ino -> ArduinoIDE (https://www.arduino.cc/en/Main/Software)

*****************************************************************************************

### Used libraries:

Code:
* MPU9250: https://github.com/bolderflight/MPU9250
* PS2-Controller: https://github.com/madsci1016/Arduino-PS2X
* RFM-95: https://github.com/jgromes/LoRaLib

Schematics:
* RFM-95: (https://github.com/adafruit/Fritzing-Library/blob/master/parts/Adafruit%20RFM9x%20LoRa%20Radio.fzpz)
* Lin-Voltage-Regulator (ASM1117): (https://github.com/tardate/LittleArduinoProjects/blob/master/FritzingParts/AMS1117/AMS1117.fzpz)

*****************************************************************************************

## What I Learned

* drawing schematics with Fritzing.
* improving simulation skills in LTSpice.
* creating switch-mode power circuits.
* improving i²c and spi skills.
* programming a regulator.
* communication via LoRa-radio modules.
* using linear voltage regulators.

## What I would change next time

* use a bigger drone frame
* use 7.4V LiPo cells and a 5V regulator
* use a radio module with a higher bandwith to be able to stream video
