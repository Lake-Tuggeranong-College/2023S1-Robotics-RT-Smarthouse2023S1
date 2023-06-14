# Design Document

## Smart Device Theme


Smart Home Automation System:

This smart home automation system can monitor and control various aspects of a home environment. These aspects include a security system, lighting control, parcel detection and logging of events to troublelshoot problems. It incorporates multiple inputs and outputs for enhanced functionality and user experience. This integrated smart home automation system provides enhanced security, convenience, and energy management capabilities by leveraging the inputs from various sensors and controlling the outputs accordingly.

## Behaviours

Lighting Control:

The potentiometer can adjust the overall brightness of the lights in the home. Rotating the potentiometer can dim or brighten the lights accordingly, providing customizable lighting levels.

Security System:
The crash sensor and PIR sensor can collectively form a comprehensive security system.
If the crash sensor is pressed it causes a house lockdown which locks all doors and releases security screens over the windows. This is represented by the dc motor being activated.
The PIR sensor detects human presence and can be used to activate the security system when no one is expected to be present. It triggers the red LED and piezo buzzer to notify the occupants.

Parcel Detection:
The line sensor can be used to detect whether a parcel has been left in its location. This is achieved by planting the line sensor in the ground facing up so when a parcel is placed on it, the line sensor gets activated. This results in logging to the SD card as well as turning on the yellow LED.

Proximity Detection:
The sonar sensor can be employed to detect the distance to objects or obstacles in the environment.
If an object is detected within a specified range, it can activate the servo motor to adjust the position of a surveillance camera which would use the sonars distance to accurately point at the target.

Data Logging and Analysis:
The SD card can be utilized for logging data related to various sensors in the system.
Sensor readings, timestamps, and any relevant information can be stored on the SD card for future analysis, system optimization, or security purposes.

