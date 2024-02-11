#!/usr/bin/env python3

"""
created by waldhauser

This file contains the programm to drive the arm back to middle and drive the robot back to home
This file is needed for the hard code driving operations 
The plant where the robot is has to be passed as argument
"""

from ev3dev2.motor import Motor, LargeMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D, SpeedPercent
from ev3dev2.sensor.lego import TouchSensor, UltrasonicSensor  
from ev3dev2.sensor import INPUT_1, INPUT_4
import sys

motorLeft = LargeMotor(OUTPUT_D)
motorRight = LargeMotor(OUTPUT_A)
motorUpDown = Motor(OUTPUT_C)
motorLeftRight = Motor(OUTPUT_B)
sensorUltraSonic = UltrasonicSensor(INPUT_4)
sensorTouch = TouchSensor(INPUT_1)

plantID = int(sys.argv[1])

# Set direction of arm rotation back to middle
if plantID % 2 == 0:
    leftRight = 50     # rotating right
else:
    leftRight = -50      # rotating left

motorUpDown.on_for_seconds(SpeedPercent(-50), seconds=2.8)
motorLeftRight.on_for_degrees(SpeedPercent(leftRight), 400)

motorLeft.on(SpeedPercent(-70), block=False)
motorRight.on(SpeedPercent(-70))

while True:
    if sensorUltraSonic.distance_centimeters < 10:
        motorLeft.on(SpeedPercent(-25), block=False)
        motorRight.on(SpeedPercent(-25))
        break

sensorTouch.wait_for_pressed(timeout_ms=None, sleep_ms=10)
motorLeft.off()
motorRight.off()