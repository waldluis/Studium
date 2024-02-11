#!/bin/bash

# Script to automatically start the robot operating programm 
# Has to be included to autostart of the RaspberryPi

cd ~/Documents/GIT/projektarbeit_duelger_waldhauser_caliskan/
source .venv/bin/activate
cd software/roboter/raspy
python3 mainProg.py