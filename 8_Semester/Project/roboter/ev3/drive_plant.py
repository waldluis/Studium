#!/usr/bin/env pybricks-micropython

"""
created by waldhauser

This file contians the programm to drive to a specific plant based on the color codes 
The plant where the robot is has to be passed as argument
"""

from ev3dev2.motor import Motor, LargeMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D, SpeedPercent
from ev3dev2.sensor.lego import ColorSensor
from ev3dev2.sensor import INPUT_2
import sys

motorRight = LargeMotor(OUTPUT_A)
motorLeft = LargeMotor(OUTPUT_D)
motorUpDown = Motor(OUTPUT_C)
motorLeftRight = Motor(OUTPUT_B)

sensorColor = ColorSensor(INPUT_2)

plantID = int(sys.argv[1])

# Set color according to plant number
if plantID == 1 or plantID == 2:
    colorCode = ColorSensor.COLOR_RED
elif plantID == 3 or plantID == 4:
    colorCode = ColorSensor.COLOR_GREEN
elif plantID == 5 or plantID == 6:
    colorCode = ColorSensor.COLOR_BLUE

# Set direction of arm rotation
if plantID % 2 == 0:
    leftRight = -50     # rotating left
else:
    leftRight = 50      # rotating right


motorRight.on(SpeedPercent(70), block=False)
motorLeft.on(SpeedPercent(70))

while True:
    if sensorColor.color == colorCode:
        break

motorLeft.off()
motorRight.off()

motorLeftRight.on_for_degrees(SpeedPercent(leftRight), 400)
motorUpDown.on_for_seconds(SpeedPercent(50), seconds=2.8)