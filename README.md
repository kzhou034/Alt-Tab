# Introduction to Embedded Systems Project - Fall 2022

Solo project for Introduction to Embedded Systems class.

## Alt-Tab

Alt-Tab is a simple final project for the Introduction to Embedded Systems class at UCR. The idea of the project is that someone moves close to the sensor, and the hardware will tell you how close that person is. Once the person is close enough, the hardware will respond by physically pressing the 'alt' and 'tab' keys to switch windows.

The three hardware complexities I chose for the project were:
- Ultrasonic Sensor: used to detect how far an object was from the sensor in centimeters
- Two Servo Motors: based on the distance obtained from the Ultrasonic Sensor, the servo motors would move. If the object is within a certain distance, one of the motors will move. If the object is close than that, both motors will move.
- Nokia 5110 LCD Screen: displays a generalization of how far an object is from the sensor. (Example: over 15 centimeters, under 15 centimeters, under 5 centimeters)

> **NOTE:** For the project, we were not allowed to use any existing functions or libraries for the hardware complexities we chose. ***All functionality for the hardware had to be created from scratch.***

The project was constructed in a smaller scale for demonstration purposes.

## Video Demo

[![Alt-Tab Demo](https://img.youtube.com/vi/2yt9DnhKEvY/0.jpg)](https://www.youtube.com/watch?v=2yt9DnhKEvY)
