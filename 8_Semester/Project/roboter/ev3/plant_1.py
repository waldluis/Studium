#!/usr/bin/env pybricks-micropython

"""
created by waldhauser

This file contians the programm to drive a specfic plant with a certain distance to drive 
"""

from ev3dev2.motor import Motor, LargeMotor, ServoMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D, SpeedPercent

motorRight = LargeMotor(OUTPUT_A)
motorLeft = LargeMotor(OUTPUT_D)
motorUpDown = Motor(OUTPUT_C)
motorLeftRight = Motor(OUTPUT_B)

motorRight.on_for_seconds(SpeedPercent(70), seconds=0.8, block=False)
motorLeft.on_for_seconds(SpeedPercent(70), seconds=0.8)

motorLeftRight.on_for_degrees(SpeedPercent(50), 400)

motorUpDown.on_for_seconds(SpeedPercent(50), seconds=2.8)
