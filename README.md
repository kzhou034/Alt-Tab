# Introduction to Embedded Systems Project - Fall 2022

Solo project for Introduction to Embedded Systems class.

## Alt-Tab

Alt-Tab is a simple final project for the Introduction to Embedded Systems class at UCR. The idea of the project is that someone moves close to the sensor, and the hardware will tell you how close that person is. Once the person is close enough, the hardware will respond by physically pressing the 'alt' and 'tab' keys to switch windows.

### Introduction

Alt-Tab is an alert system that quickly switches between two windows when it detects that there is an object near the sensor. Based on the reading from the sensor, the first servo motor moves, and if the object gets closer the second one begins to move. If an object is within a certain distance of the sensor, it outputs a message onto the LCD screen saying that something is within X centimeters away from the sensor, or it is over X centimeters away from the sensor. 

A major bug that came up during the implementation of the project was that at times, after both of the servo motors move and the object slowly moves away from the sensor, the first servo motor doesn’t move even though it is within range. Another bug was that the screen also outputted a black box behind the message, which made it difficult to read the message that was displayed on the screen. 

### Complexities

The three hardware complexities I chose for the project were:
- Ultrasonic Sensor: used to detect how far an object was from the sensor in centimeters
- Two Servo Motors: based on the distance obtained from the Ultrasonic Sensor, the servo motors would move. If the object is within a certain distance, one of the motors will move. If the object is close than that, both motors will move.
- Nokia 5110 LCD Screen: displays a generalization of how far an object is from the sensor. (Example: over 15 centimeters, under 15 centimeters, under 5 centimeters)

### User Guide

The purpose of this project is so that if something or someone gets close to your sensor, you are able to switch windows so that the incoming object can’t directly see what you’re doing. The screen outputs a message saying how close the object is to where the sensor was placed. 

Say you placed the sensor at your door handle and your mom is about to scold you for not doing your homework. You are in the middle of watching a video and you don’t hear her approaching. As she gets closer, the first servo will begin to move to hit the Alt key, and if she is about to touch the door knob the second servo motor will move to hit the Tab key. The screen outputs a message if an object (such as a person) is within a certain range of the sensor. For example, if the range is 15 centimeters, and the sensor only detects an object that is over 15 centimeters  away, the screen displays “over 15.” If it senses an object is within 15 centimeters, the screen displays “less than 15.”

### Hardware Components Used
- Arduino UNO R3 Controller Board
- Ultrasonic Sensor
- Nokia 5110 LCD
- x2 Servo Motor SG90
- Jumper wires
- Breadboard
- x5 1k resistors
- 10k resistor

### Software Libraries Used
- SPI library: I used it to send data to the LCD screen to control how to output the messages.
- Arduino library: I used digitalWrite to interact with certain pins, delay() functions to implement the servo motors, and attachInterrupt() to help implement the ultrasonic sensor. 

> **NOTE:** For the project, we were not allowed to use any existing functions or libraries for the complexities we chose. ***All functionality for the complexities had to be implemented from scratch.***

### Wiring Diagram

<img width="476" alt="wiring diagram" src="https://github.com/user-attachments/assets/3162cab7-e766-4e5d-a48f-bd7fcd3e15e3">

## Video Demo

The project was constructed in a smaller scale for demonstration purposes.

[![Alt-Tab Demo](https://img.youtube.com/vi/2yt9DnhKEvY/0.jpg)](https://www.youtube.com/watch?v=2yt9DnhKEvY)
