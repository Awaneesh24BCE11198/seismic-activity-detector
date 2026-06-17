# I2C-Based Seismic Activity Detector 

A localized, real-time seismic activity detector built with an **Arduino Nano** and an **ADXL345 3-axis digital accelerometer**. 

This system calculates the 3D magnitude vector of physical force over an I2C communication bus. If the total physical acceleration exceeds a calibrated threshold of 1.25g, it triggers an immediate audio-visual alarm system (Active-Low Piezo Buzzer & LED Strobe).

## Hardware Components
* Microcontroller: Arduino Nano V3.0 (ATmega328P)
* Sensor: ADXL345 3-Axis Accelerometer Breakout (Digital I2C)
* Outputs: 5V Active-Low Piezo Buzzer, 5mm Red LED
* Passives: 330Ω Resistor

## How It Works
1. The ADXL345 sensor constantly sends X, Y, and Z axis acceleration data to the Arduino.
2. The Arduino stitches the raw bytes into integers and calculates the absolute vector magnitude.
3. If the magnitude is `< 1.5g` (Normal resting gravity is 1.0g), the system remains armed and silent.
4. If the magnitude is `> 1.5g` (Simulating a seismic shock), the alarms trigger immediately until the system stabilizes.

## Repository Contents
* `code.ino` - The primary Embedded C++ logic for the Arduino.
* `Earfquake.fzz` - The Fritzing circuit schematic and breadboard layout.
* `Gerber_Files.zip` - Extended Gerber files for PCB fabrication.
