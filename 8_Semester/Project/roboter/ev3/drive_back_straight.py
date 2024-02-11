#!/usr/bin/env python3

"""
created by waldhauser

This file contains the programm to drive the robot back to the starting position 
This file is needed for the color code drive operation
No arguments are needed
The end is determined by the UltraSonic- and TouchSensor
"""

from ev3dev2.motor import LargeMotor, OUTPUT_A, OUTPUT_D, SpeedPercent
from ev3dev2.sensor.lego import TouchSensor, UltrasonicSensor  
from ev3dev2.sensor import INPUT_1, INPUT_4

motorLeft = LargeMotor(OUTPUT_D)
motorRight = LargeMotor(OUTPUT_A)
sensorUltraSonic = UltrasonicSensor(INPUT_4)
sensorTouch = TouchSensor(INPUT_1)

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