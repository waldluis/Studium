"""
created by caliskan at 19.04.2023

This file contains the main script for the backend server of smart garden project
It has the task to be a bridge between the frontend and robot.
It also contains a database with the current plant data
Used protocol for interaction: mqtt (paho-mqtt module)
"""

# imports
import paho.mqtt.client as mqtt
from defines import MQTT_BROKER_LOCAL, MQTT_BROKER_GLOBAL, Topics, BACKEND_CLIENT_ID, DATABASE_NAME
from plantdatabase import PlantDataBase
import data_functions
import logging
import sys
from robot import Robot


def on_connect(_client: mqtt.Client, _userdata, _flags, _rc, _mydatabase, _robot):
    """
    This method gets called, when it connects to a mqtt broker.
    It is used to subscribe to the specific topics
    :param _robot: robot object for
    :param _mydatabase: object, that contains the custom plant database and methods for its usage
    :param _client: mqtt client object
    :param _userdata:
    :param _flags:
    :param _rc: connection flag
    :return: none
    """
    if _rc == 0:
        print("connected")

        # TOPIC SUBSCRIPTIONS

        # From Robot:
        _client.subscribe(Topics['ROBOT_DATA_SENSORDATA'])
        _client.message_callback_add(Topics['ROBOT_DATA_SENSORDATA'], lambda client, userdata, message: data_functions.
                                     data_sensordata(client, userdata, message, _mydatabase, _robot))

        _client.subscribe(Topics['ROBOT_DATA_ALL'])
        _client.message_callback_add(Topics['ROBOT_DATA_ALL'], lambda client, userdata, message: data_functions.
                                     data_sensordataall(client, userdata, message, _mydatabase, _robot))
        _client.subscribe(Topics['ROBOT_DATA_POSITION'])
        _client.message_callback_add(Topics['ROBOT_DATA_POSITION'], data_functions.data_position)

        _client.subscribe(Topics['ROBOT_DATA_BATTERY'])
        _client.message_callback_add(Topics['ROBOT_DATA_BATTERY'], lambda client, userdata, message: data_functions.
                                     data_battery(client, userdata, message, _robot))

        _client.subscribe(Topics['ROBOT_DATA_ERROR'])
        _client.message_callback_add(Topics['ROBOT_DATA_ERROR'], lambda client, userdata, message: data_functions.
                                     data_error(client, userdata, message, _robot))

        _client.subscribe(Topics['ROBOT_DATA_ROBOTREADY'])
        _client.message_callback_add(Topics['ROBOT_DATA_ROBOTREADY'], lambda client, userdata, message: data_functions.
                                     data_robotready(client, userdata, message, _robot))

        # From FrontEnd:
        _client.subscribe(Topics['BACKEND_ACTION_DRIVE'])
        _client.message_callback_add(Topics['BACKEND_ACTION_DRIVE'], lambda client, userdata, message: data_functions.
                                     action_drive(client, userdata, message, _mydatabase, _robot))

        _client.subscribe(Topics['BACKEND_ACTION_DRIVEALL'])
        _client.message_callback_add(Topics['BACKEND_ACTION_DRIVEALL'], lambda client, userdata, message: data_functions.
                                     action_driveall(client, userdata, message, _mydatabase, _robot))

        _client.subscribe(Topics['BACKEND_ACTION_GETPOSITION'])
        _client.message_callback_add(Topics['BACKEND_ACTION_GETPOSITION'], data_functions.action_getposition)

        _client.subscribe(Topics['BACKEND_ACTION_GETBATTERY'])
        _client.message_callback_add(Topics['BACKEND_ACTION_GETBATTERY'], data_functions.action_getbattery)

        _client.subscribe(Topics['BACKEND_ACTION_GETALLDATA'])
        _client.message_callback_add(Topics['BACKEND_ACTION_GETALLDATA'],
                                     lambda client, userdata, message: data_functions.
                                     action_getalldata(client, userdata, message, _mydatabase))

        _client.subscribe(Topics['BACKEND_ACTION_NEWPLANT'])
        _client.message_callback_add(Topics['BACKEND_ACTION_NEWPLANT'], lambda client, userdata, message: data_functions.
                                     action_newplant(client, userdata, message, _mydatabase))

        _client.subscribe(Topics['BACKEND_ACTION_CONFIGUREPLANT'])
        _client.message_callback_add(Topics['BACKEND_ACTION_CONFIGUREPLANT'], lambda client, userdata, message: data_functions.
                                     action_configureplant(client, userdata, message, _mydatabase))

        _client.subscribe(Topics['BACKEND_ACTION_DELETEPLANT'])
        _client.message_callback_add(Topics['BACKEND_ACTION_DELETEPLANT'],
                                     lambda client, userdata, message: data_functions.
                                     action_deleteplant(client, userdata, message, _mydatabase))

        _client.subscribe(Topics['BACKEND_ACTION_PLANTCOUNT'])
        _client.message_callback_add(Topics['BACKEND_ACTION_PLANTCOUNT'], lambda client, userdata, message: data_functions.
                                     action_countplants(client, userdata, message, _mydatabase))

        # END TOPIC SUBSCRIPTIONS
    else:
        print("connection failed")


def main():
    # Create Robot Object
    robot = Robot()

    # Connect to Plant_Database and create tables if database did not exist
    my_database = PlantDataBase(database_name=DATABASE_NAME)
    my_database.create_tables()

    # Create MQTT Client and connect to local broker
    mqttclient = mqtt.Client(BACKEND_CLIENT_ID, """transport="websockets""""")  # transport websockets required for local broker
    mqttclient.on_connect = lambda client, userdata, flags, rc: on_connect(_client=client,
                                                                           _userdata=userdata,
                                                                           _flags=flags,
                                                                           _rc=rc,
                                                                           _mydatabase=my_database,
                                                                           _robot=robot)
    mqttclient.connect(MQTT_BROKER_GLOBAL)

    # Initialize logger and save in server.log file
    logging.basicConfig(filename="server.log", filemode="a", encoding="utf-8", level=logging.DEBUG,
                        format='%(asctime)s %(name)s %(levelname)s %(message)s',
                        datefmt="%d-%m-%Y %H:%M:%S")
    logging.getLogger().addHandler(logging.StreamHandler(sys.stdout))

    # Starting mqttclient infinite loop
    mqttclient.loop_forever()


if __name__ == "__main__":
    main()
