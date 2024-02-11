"""
created by waldhauser

This file contains the functions for the mainProg.py. 
The functions are part of three groups, MQTT-callbacks, functions for external threads and one normal function.
"""

import paho.mqtt.client as mqtt
import json
import threading
import os
import logging
import raspy_sensors as Sensors
from defines import Topics, SENSORDATA, ALLSENSORDATA


def measure_send_data(plantID, actionID, client: mqtt.Client):
    """
    Reads all sensors and publishes data via MQTT in form of SENSORDATA

    ***Function is only neccessary for driving without color codes*** 

    Args:
        plantID (_type_): plant to measure
        actionID (_type_): current ID of driving action
        client (mqtt.Client): current mqtt client for publishing
    """
    sensorData = {}
    sensorData |= SENSORDATA

    try:
        Sensors.readSensors(sensorData)
    except Exception as e:
        logging.error(str(e))
        client.publish(Topics["ROBOT_DATA_ERROR"], str(e), qos=1)

    sensorData["PlantID"] = plantID
    sensorData["ActionID"] = actionID
    client.publish(Topics["ROBOT_DATA_SENSORDATA"], json.dumps(sensorData, indent=4), qos=1)

#region Thread
# Functions to be executed in external Thread to not block the mainProg
# Functions contain the drive and sensor measurement operations

def drive_plant_thread(plantID, actionID, client: mqtt.Client):
    """
    Function to drive to plant according to number from MQTT message in thread
    Drive programm based on hardcoded drive programms specific for each plant
    Only possible to drive to one plant per execution
    Meassure and publish data via MQTT
    Drive home to starting point

    ***Function is only neccessary for driving without color codes*** 

    Args:
        plantID (_type_): plant to measure
        actionID (_type_): current ID of driving action 
        client (mqtt.Client): current mqtt client for publishing
    """

    errorCode = os.system(f'sshpass -p maker ssh robot@ev3dev.local python3 /home/robot/Programme/plant_{plantID}.py')

    # Error handling for drive operation
    # Abort when drive operation at start when error occurs
    if errorCode != 0:
        if errorCode == 65280:
            errorMessage = "EV3 not connected"
        else:
            errorMessage = "Motor or Sensor unplugged"
         
        logging.error(f"{errorMessage}, Drive Plant aborted, Robot at starting position")
        client.publish(Topics["ROBOT_DATA_ERROR"], f"{errorMessage}, Drive Plant aborted, Robot at starting position", qos=1)
        client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)
        return
   
    logging.info("Measuring Sensors")
    measure_send_data(plantID, actionID, client)

    # Taking Picture not fully implemented
        # logging.info("Taking Picture")
        # sendPicture(client)

    logging.info("Robot driving home")
    errorCode = os.system(f'sshpass -p maker ssh robot@ev3dev.local python3 /home/robot/Programme/drive_back.py {plantID}')

    # Error handling for drive operation
    # Abort when drive operation at start when error occurs
    if errorCode != 0:
        if errorCode == 65280:
            errorMessage = "EV3 not connected"
        else:
            errorMessage = "Motor or Sensor unplugged"
         
        logging.error(f"{errorMessage}, Drive Plant aborted, Robot at starting position")
        client.publish(Topics["ROBOT_DATA_ERROR"], f"{errorMessage}, Drive Plant aborted, Robot at plant {plantID}", qos=1)
        client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)
        return

    logging.info("Robot home")
    client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)


def drive_plant_all_thread(plantIDs: list, actionID, client: mqtt.Client):
    """
    Function to drive to plants according to numbers from MQTT message in thread, one or more plants possible
    PlantIDs have to be in ascending order
    Drive programm based on color codes in the flowerbed
    Meassure and publish data for all plants via MQTT
    Drive home to starting point

    ***If color codes are working properly, only this function is needed for drive operations***

    Args:
        plantIDs (list): Plants to drive to, plants have to be in ascending order
        actionID (_type_): ActionID from Backend for whole drive action
        client (mqtt.Client): current MQTT client
    """

    allPlantData = {                        # Sensordata for all plants
        "SensorData": [],
        "ActionID": ""
    }
        
    allPlantData["ActionID"] = actionID

    for plant in plantIDs:
        logging.info(f"Robot Driving to plant {plant}")
        errorCode = os.system(f'sshpass -p maker ssh robot@ev3dev.local python3 /home/robot/Programme/drive_plant.py {plant}')

        # Error handling for drive operation
        # Abort when drive operation at start when error occurs
        if errorCode != 0:
            if errorCode == 65280:
                errorMessage = "EV3 not connected"
            else:
                errorMessage = "Motor or Sensor unplugged"
         
            logging.error(f"{errorMessage}, Drive Plant aborted, Robot at starting position")
            client.publish(Topics["ROBOT_DATA_ERROR"], f"{errorMessage}, Drive Plant aborted, Robot at starting position", qos=1)
            client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)
            return
    

        # Read Sensors and store data, take picture
        logging.info("Measuring Sensors")
        try:
            sensordata = {}
            sensordata |= SENSORDATA
            Sensors.readSensors(sensordata)
        except Exception as e:
            logging.error(str(e))
            client.publish(Topics["ROBOT_DATA_ERROR"], str(e), qos=1)

        sensordata["PlantID"] = plant
        allPlantData["SensorData"].append(sensordata)


        # Taking Picture not fully implemented
        # logging.info("Taking Picture")
        # sendPicture(client)

        errorCode = os.system(f'sshpass -p maker ssh robot@ev3dev.local python3 /home/robot/Programme/drive_arm.py {plant}')
        # Error handling for drive operation
        # Abort when drive operation at start when error occurs
        if errorCode != 0:
            if errorCode == 65280:
                errorMessage = "EV3 not connected"
            else:
                errorMessage = "Motor or Sensor unplugged"
         
            logging.error(f"{errorMessage}, Drive Plant aborted, Robot at plant {plant}")
            client.publish(Topics["ROBOT_DATA_ERROR"], f"{errorMessage}, Drive Plant aborted, Robot at plant {plant}", qos=1)
            client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)
            return

    # End of drive and measure operation
    logging.info("All Plants measured, sending data")
    client.publish(Topics["ROBOT_DATA_ALL"], json.dumps(allPlantData, indent=4), qos=1)


    logging.info("Robot driving home")
    # Error handling for drive operation
    # Abort when drive operation at start when error occurs
    errorCode = os.system(f'sshpass -p maker ssh robot@ev3dev.local python3 /home/robot/Programme/drive_back_straight.py')
    if errorCode != 0:
        if errorCode == 65280:
            errorMessage = "EV3 not connected"
        else:
            errorMessage = "Motor or Sensor unplugged"
         
        logging.error(f"{errorMessage}, Drive Plant aborted, Robot at starting position")
        client.publish(Topics["ROBOT_DATA_ERROR"], f"{errorMessage}, Drive Plant aborted, Robot at plant {plant}", qos=1)
        client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)
        return

    logging.info("Robot home")
    client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "True", qos=1)

#endregion

#region MQTT callbacks
# Functions to be called by the MQTT callbacks
# Starting the drive operations in threads or executing the small operations directly

def drive_plant(client: mqtt.Client, userdata, message: mqtt.MQTTMessage):
    """
    Function to drive to plant according to request
    Starting Drive in Thread to not block main programm

     ***Function is only neccessary for driving without color codes*** 

    Args:
        client (mqtt.Client): current mqtt client
        userdata (_type_): _description_
        message (mqtt.MQTTMessage): received DRIVE message with PlantID and ActionID
    """
    dictMessage = json.loads(str(message.payload.decode("UTF-8")))

    plantID = dictMessage["PlantID"]
    actionID = dictMessage["ActionID"]

    logging.info(f"Received Drive-request to plant {plantID}, ActionID: {actionID}")
    client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "False", qos=1)
    
    thread = threading.Thread(target= drive_plant_thread, args=(plantID, actionID, client), daemon=True)
    thread.start()


def drive_plant_all(client: mqtt.Client, userdata, message: mqtt.MQTTMessage):
    """
    Function to drive to plants according to request
    Starting Drive in Thread to not block main programm

    ***If color codes are working properly, only this function is needed for drive operations***

    Args:
        client (mqtt.Client): current MQTT client
        userdata (_type_): _description_
        message (mqtt.MQTTMessage): received DRIVEALL message with PlantIDs and ActionID
    """
    dictMessage = json.loads(str(message.payload.decode("UTF-8")))

    plantIDs = dictMessage["PlantID"]            # List of numbers
    actionID = dictMessage["ActionID"]

    logging.info(f"Received Drive-request to plants {plantIDs}, ActionID: {actionID}")
    client.publish(Topics["ROBOT_DATA_ROBOTREADY"], "False", qos=1)
    
    thread = threading.Thread(target= drive_plant_all_thread, args=(plantIDs, actionID, client), daemon=True)
    thread.start()


def get_position(client: mqtt.Client, userdata, message: mqtt.MQTTMessage):
    """
    Callback function for GPS position request
    Function to send actual GPS position via MQTT in form of POSITION

    ***Not implemented, available GPS-sensor was not working***

    Args:
        client (mqtt.Client): current mqtt client
        userdata (_type_): _description_
        message (mqtt.MQTTMessage): received message
    """
    logging.info("Received position request")

    position = {
        "Position": ""
    }

    client.publish(Topics["ROBOT_DATA_POSITION"], json.dumps(position, indent=4), qos=1)


def get_batteryStatus(client: mqtt.Client, userdata, message: mqtt.MQTTMessage):
    """
    Callback function for battery status request
    Function to read battery status from EV3 and send via MQTT in form of BATTERY
    Current battery level is stored in "voltage_now" file
    Reading battery level via SSH script execution
    Battery level shown in Volts:
    8,5V -> 100%
    5V -> 0%

    Args:
        client (mqtt.Client): current mqtt client
        userdata (_type_): _description_
        message (mqtt.MQTTMessage): received message
    """
    logging.info("Received battery status request")

    try:
        batteryLevel = int(os.popen('sshpass -p maker ssh robot@ev3dev.local cat /sys/devices/platform/battery/power_supply/lego-ev3-battery/voltage_now').read())
    except:
        logging.error("EV3 not connected")
        client.publish(Topics["ROBOT_DATA_ERROR"], "EV3 not connected", qos=1)
        return

    batteryLevel = round(batteryLevel / 1000000, 2)       # Conversion to Volt
    batteryLevel = batteryLevel - 5
    batteryLevel = round(batteryLevel / 3.5, 3) *100      # Conversion to Percentage, 8,5V -> 100%, 5V -> 0%

    battery = {
        "Battery": batteryLevel
    }
    client.publish(Topics["ROBOT_DATA_BATTERY"], json.dumps(battery, indent=4), qos=1)
    logging.info(f"Battery done {batteryLevel}")


def sendPicture(client: mqtt.Client):
    """
    Takes picture and publish via MQTT

    ***Pictures can not be send until now -> assumption of reaching maximum payload limit***

    Args:
        client (mqtt.Client): current mqtt client
    """
    try:
        Sensors.takePicture()
    except Exception as e:
        logging.error(str(e))
        client.publish(Topics["ROBOT_DATA_ERROR"], str(e), qos=1)
        return

    with open("picture.png", "rb") as f:
        file = f.read()
        byteArr = bytearray(file)
        client.publish(Topics["ROBOT_DATA_PICTURE"], byteArr)
        logging.info("Picture Published")

#endregion