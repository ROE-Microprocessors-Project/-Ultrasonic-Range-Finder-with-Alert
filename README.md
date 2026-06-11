# Ultrasonic Range Finder with Alert

**Microprocessors Course Project - Medipol University**

*Team :Armita Sadat Momenzadeh, Sina Zaker, Mohammadmatin Farboodi*

## Overview
This repository contains the C source code for our physical breadboard project: an Ultrasonic Range Finder. The system uses an HC-SR04 sensor to measure the distance to an object and triggers a buzzer and LED alert if things get too close. The project runs on a **PIC16F877A** microcontroller. 

## How It Works
* **Timer1 (Pulse Width Measurement):** We used the 16-bit Timer1 to count exactly how long it takes for the ultrasonic echo to bounce back. We turn the timer on when the echo pin goes high and stop it when it goes low.
* **GPIO (Trigger/Echo):** We configured standard digital pins to communicate with the sensor (RC0 as output for the trigger, RC1 as input for the echo). We also used RD0 as an output to turn on the warning LED.
* **PWM (Buzzer Control):** Instead of just using a basic high/low signal, we used the CCP1 module to generate a proper PWM signal on pin RC2 to drive the buzzer. 
* **Time-based measurement & Accurate calculation:** The core concept is timing the speed of sound. We take the raw timer ticks and divide them by a specific calibration number (36) to accurately calculate the distance in centimeters. We also added code timeouts so the system resets and doesn't freeze if an echo gets lost.

## Alert Zones
* **0-10 cm:** Too close. LED stays on and the buzzer sounds continuously.
* **11-20 cm:** Warning zone. LED turns on and the buzzer beeps rapidly.
* **Over 20 cm:** Safe. LED and buzzer are off.

## Hardware Components
* Microcontroller: PIC16F877A
* Sensor: HC-SR04 Ultrasonic Sensor
* Oscillator: 20MHz Crystal with 2x 22pF Ceramic Capacitors
* Alerts: 5V Active Buzzer and an LED
* Resistors: 10kΩ (MCLR pull-up) and 220Ω (LED)
* Programmer: PICkit 3
* Power: External 5V Lab Power Supply
* Breadboard and jumpers

## Pin Connections
| Component | Function | PIC16F877A Pin | Pin Type |
| :--- | :--- | :--- | :--- |
| **HC-SR04** | Trigger (TRIG) | RC0 | Output |
| **HC-SR04** | Echo (ECHO) | RC1 | Input |
| **Buzzer** | PWM Alert | RC2 (CCP1) | Output |
| **LED** | Visual Alert | RD0 | Output |

### Flashing the Code
1. Compile the `main.c` file using XC8 to generate the `.hex` file.
2. Connect the **PICkit 3** to your computer and wire it to the ICSP pins on the microcontroller.
3. Use MPLAB IPE to load the `.hex` file and program the chip.

### Running the Circuit
1. Disconnect the PICkit 3.
2. Connect the external **5V Lab Power Supply** to the power rails on your breadboard.
3. Turn on the power supply and move your hand in front of the sensor to test the distance alerts.

## Team 
* Armita Sadat Momenzadeh
* Sina Zaker
* Mohammadmatin Farboodi
