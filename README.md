# Ultrasonic Motion Detector with Telegram

## Introduction

This repository contains the code for an ultrasonic motion detector that can send notifications to a Telegram chat when motion is detected. The code is written for the ESP32 microcontroller and is designed to work with a HC-SR04 ultrasonic sensor.

## Requirements

- ESP32 microcontroller
- HC-SR04 ultrasonic sensor
- Telegram account
- Microsoft Visual Studio (if modifying the code)
- Arduino IDE

## Installation

1. Clone the repository to your local machine.
2. Connect the ESP32 microcontroller and HC-SR04 ultrasonic sensor according to the following diagram:
   - VCC of the sensor to 3.3V of the ESP32
   - Trig of the sensor to pin 26 of the ESP32
   - Echo of the sensor to pin 27 of the ESP32
   - GND of the sensor to GND of the ESP32
3. Upload the code to the ESP32 using the Arduino IDE or other compatible software.
4. Enter your Wi-Fi credentials and Telegram Bot Token in the code.
5. Upload the code to the ESP32.
6. Open the solution in Visual Studio.
7. Build the solution and run the application.

## Features

- Detects motion using an ultrasonic sensor
- Sends notifications to a Telegram chat when motion is detected
- Easy to set up and use

## Code

The code for the ESP32 microcontroller is already included in the repository.

## Contributions

Contributions are welcome! If you'd like to make changes to the code or add new features, feel free to create a pull request.
