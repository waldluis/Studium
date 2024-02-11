"""
created by waldlhauser

This file contains the main script for the RaspberryPi of smart garden project
It has the task to control the EV3 robot and take measurements with the mounted sensors
The sensor data is published to MQTT topics to be available for the backend server
Used protocol for interaction: mqtt (paho-mqtt module)
Interaction with the EV3 via SSH
"""

import paho.mqtt.client as mqtt
import functions
import logging
import sys
from defines import Topics, RASPI_CLIENT_ID, MQTT_BROKER_GLOBAL, MQTT_BROKER_LOCAL


def on_connect(client: mqtt.Client, userdata, flags, rc):
    """
    This method gets called, when it connects to a mqtt broker.
    It is used to subscribe to the specific topics

    Args:
        client (mqtt.Client): current mqtt client
        userdata (_type_): _description_
        flags (_type_): _description_
        rc (_type_): _description_
    """
    if rc == 0:
        #Add callbacks
        client.message_callback_add(Topics["ROBOT_ACTION_DRIVE"], functions.drive_plant)
        client.message_callback_add(Topics["ROBOT_ACTION_GETPOSITION"], functions.get_position)
        client.message_callback_add(Topics["ROBOT_ACTION_GETBATTERY"], functions.get_batteryStatus)
        client.message_callback_add(Topics["ROBOT_ACTION_DRIVEALL"], functions.drive_plant_all)

        #Subscribe to topics
        client.subscribe(Topics["ROBOT_ACTION_DRIVE"])
        client.subscribe(Topics["ROBOT_ACTION_GETPOSITION"])
        client.subscribe(Topics["ROBOT_ACTION_GETBATTERY"])
        client.subscribe(Topics["ROBOT_ACTION_DRIVEALL"])

        logging.info("MQTT initialized")    
    


def main():
    """
    Initialises MQTT
    Runs forever and controlls all robot functions
    """
    logging.basicConfig(filename="robot.log", filemode="a", encoding="utf-8", level=logging.DEBUG, format='%(asctime)s %(name)s %(levelname)s %(message)s',
                    datefmt="%d-%m-%Y %H:%M:%S")
    logging.getLogger().addHandler(logging.StreamHandler(sys.stdout))

    # client = mqtt.Client(RASPI_CLIENT_ID)
    client = mqtt.Client(RASPI_CLIENT_ID, transport="websockets")        # Local Broker
    client.on_connect = on_connect
    # client.connect(MQTT_BROKER_GLOBAL)
    client.connect("192.168.137.197")                                  # Local Broker

    logging.info("Robot initialised")

    client.loop_forever()                   # Loop_start not needed


if __name__ == "__main__":
    main()