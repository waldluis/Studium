#!/usr/bin/env python3

"""
created by waldhauser

This file contains the programm to drive the arm back to middle 
This file is needed for the color code drive operation
The plant where the robot is has to be passed as argument
"""

from ev3dev2.motor import Motor, OUTPUT_B, OUTPUT_C, SpeedPercent
import sys

motorUpDown = Motor(OUTPUT_C)
motorLeftRight = Motor(OUTPUT_B)

plantID = int(sys.argv[1])

# Set direction of arm rotation back to middle
if plantID % 2 == 0:
    leftRight = 50     # rotating right
else:
    leftRight = -50      # rotating left

motorUpDown.on_for_seconds(SpeedPercent(-50), seconds=2.8)
motorLeftRight.on_for_degrees(SpeedPercent(leftRight), 400)
