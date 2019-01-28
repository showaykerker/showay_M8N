# showay_M8N


## Description

Modified from "Using a Hobby-Ace Ublox GPS Module Built-in Compass With Arduino Uno by ScotP2" https://goo.gl/he6chg

Simply packed up extra libraries (Adafruit_Sensor.h/ Adafruit_HMC5883_U.h/ miniGPS++.h) to it and modify the output format for my project.

I tested on Ubuntu 18.04 LTE, Arduino Nano w/ATmega328.

## Wiring

| Wires on M8N | Pins on Arduino Nano|
|     :---     |        :--          |
| Red (5V)     | 5V                  |
| Black (GND)  | GND                 |
| Green (TX)   | D8 (RX)             |
| Yellow (RX)  | D9 (TX)             |
| Blue (SDA)   | A4 (SDA)            |
| Orange (SCL) | A5 (SCL)            |


