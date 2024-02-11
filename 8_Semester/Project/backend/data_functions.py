"""
created by caliskan at 19.04.2023

This file contains all functions, which handle the different cases.
Every function should return json format with the wanted data from the database
The functions are called, when data is received on the according channel
"""
import paho.mqtt.client as mqtt
from plantdatabase import PlantDataBase
from defines import Topics, MAX_PLANT_COUNT
import json
import uuid
from typing import Union
from datetime import datetime
import logging
from robot import Robot


# Robot Channel Reactions

def data_sensordata(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase,
                    robot: Robot):
    """
    This function is used to store received data from the robot inside the plant_database
    USAGE FOR DATA OF ONE PLANT
    :param client: mqtt client
    :param userdata:
    :param message: received data
    :param mydatabase: database information
    :param robot: robot object
    :return: none
    """

    # Load the message and convert to json
    str_in = str(message.payload.decode("UTF-8"))
    payload = json.loads(str_in)

    logging.info("ROBOT_DATA_SENSORDATA Received data: " + json.dumps(payload))
    drive_data = {
        "PlantID": [payload['PlantID']],
        "ActionID": payload['ActionID']
    }

    try:
        # Delete order from order list
        robot.delete_order(drive_data)
        # Save data in database
        mydatabase.insert_measurement_data(plant_id=payload['PlantID'],
                                           sensordata_temp=payload['AirTemperature'],
                                           sensordata_humidity=payload['AirHumidity'],
                                           sensordata_soil_moisture=payload['SoilMoisture'],
                                           sensordata_brightness=payload['Brightness'])
        logging.debug("Inserted to data base: " + json.dumps(payload))

        # Send received data to frontend
        action_getalldata(client, userdata, message, mydatabase)
    except Exception as e:
        logging.error("Could not delete order: " + str(e))


def data_sensordataall(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase,
                       robot: Robot):
    """
    This function is used to store received data from the robot inside the plant_database
    USAGE FOR DATA OF ALL PLANTS
    :param client:
    :param userdata:
    :param message:
    :param mydatabase:
    :param robot:
    :return: none
    """

    # Load the message and convert to json
    str_in = str(message.payload.decode("UTF-8"))
    payload = json.loads(str_in)
    logging.info("ROBOT_DATA_SENSORDATAALL Received data: " + json.dumps(payload))

    # Create list of plant_ids and create dataset
    plant_ids = []
    for i in payload['SensorData']:
        plant_ids.append(i["PlantID"])
    drive_data = {
        "PlantID": plant_ids,
        "ActionID": payload['ActionID']
    }

    try:
        # Delete order from order list
        robot.delete_order(drive_data)

        # Insert all received data files in plant_database
        for i in payload['SensorData']:
            mydatabase.insert_measurement_data(plant_id=i['PlantID'],
                                               sensordata_temp=i['AirTemperature'],
                                               sensordata_humidity=i['AirHumidity'],
                                               sensordata_soil_moisture=i['SoilMoisture'],
                                               sensordata_brightness=i['Brightness'])
            logging.debug("Inserted to data base: " + json.dumps(payload))

        # Send all the plant data to the frontend
        action_getalldata(client, userdata, message, mydatabase)
    except Exception as e:
        logging.error("Could not delete order: " + str(e))


def data_position(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, robot: Robot):
    """
    This function is used to receive the robot position and insert it in the robot object
    :param client: mqtt client
    :param userdata:
    :param message: received data
    :param robot: robot object to store position
    :return: none
    """

    logging.info("ROBOT_DATA_POSITION Received data: " + json.dumps(message.payload.decode("UTF-8")))

    # Store received position data in robot object
    robot.store_position(json.loads(message.payload.decode("UTF-8"))["Position"])
    position_data = {
        "Position": robot.get_position(),
        "Timestamp": str(datetime.now())
    }
    # Send the position as a json object to the frontend channel
    client.publish(Topics['BACKEND_DATA_POSITION'], json.dumps(position_data))


def data_battery(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, robot: Robot):
    """
    This function is used to receive the robot position and insert it in the robot object
    :param client: mqtt client object
    :param userdata:
    :param message: received data
    :param robot: robot object to store the received information
    :return: none
    """

    logging.info("ROBOT_DATA_BATTERY Received data: " + str(json.dumps(message.payload.decode("UTF-8"))))
    # Store battery status in robot object
    robot.store_battery(json.loads(message.payload.decode("UTF-8"))["Battery"])
    battery_data = {
        "Battery": robot.get_battery(),
        "Timestamp": str(datetime.now())
    }
    # Send Battery status and Robot-Ready Status as json objects to frontend
    client.publish(Topics['BACKEND_DATA_BATTERY'], json.dumps(battery_data))
    client.publish(Topics['BACKEND_DATA_ROBOTREADY'], str(robot.get_robot_status()))


def data_error(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, robot: Robot):
    """
    This function is called when the robot sends an error message and forwards it to the frontend
    :param client: mqtt client
    :param userdata:
    :param message: received error message
    :param robot: robot objectg
    :return: none
    """

    # Store last error in robot object
    robot.store_last_error(message.payload.decode("UTF-8"))
    # Write error into server log
    logging.error("ROBOT_DATA_ERROR new error received from Robot: " + robot.get_last_error())
    # Send error data to FrontEnd Channel to display it to the user
    client.publish(Topics['BACKEND_DATA_ERROR'], message.payload.decode("UTF-8"))


def data_robotready(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, robot: Robot):
    """
    This function is used to update the Robot-Ready Status of the Robot and inform the FrontEnd about it
    :param client:  mqtt client
    :param userdata:
    :param message: received data
    :param robot: robot object
    :return: none
    """

    # Update the robot status
    robot.change_robot_status(message.payload.decode("UTF-8") == 'True')

    # If possible send new waiting order to the robot
    if robot.get_robot_status() is True and robot.get_order_number() >= 1:
        client.publish(Topics['ROBOT_ACTION_DRIVE'], json.dumps(robot.get_next_order()))
        logging.info("Waiting Order send to Robot")

    logging.info("ROBOT_DATA_ROBOTREADY status updated: " + str(robot.get_robot_status()))

    # Send new robot-ready status to frontend channel
    client.publish(Topics['BACKEND_DATA_ROBOTREADY'], str(robot.get_robot_status()))


# FrontEnd Channel Reactions

def action_drive(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase,
                 robot: Robot):
    """
    This function is called when a drive command from the FrontEnd is received and forwards the order to the robot or
    stores it in the order list.
    :param client: mqtt client object
    :param userdata:
    :param message: information of plant to drive to
    :param mydatabase: plant_database
    :param robot: robot object
    :return: none
    """
    # Get PlantID from received PlantName
    plant_id = mydatabase.get_plant_id(plant_name=json.loads(str(message.payload.decode("UTF-8"))))

    # Generate a new ActionID
    action_id = str(uuid.uuid4())
    drive_data = {
        "PlantID": plant_id,
        "ActionID": action_id
    }

    # Store order in order list or discard if list already contains 5 orders
    if robot.get_order_number() < 6 and robot.get_robot_status() is True:
        robot.add_order({"PlantID": [plant_id], "ActionID": action_id})
        # Send order to robot, if robot is available
        client.publish(Topics['ROBOT_ACTION_DRIVE'], json.dumps(drive_data))
        logging.info("BACKEND_ACTION_DRIVE Drive Command published: " + json.dumps(drive_data))
    else:
        if robot.get_order_number() < 6:
            # Add to order list if robot not available
            robot.add_order(drive_data)
            logging.info("BACKEND_ACTION_DRIVE New data added to order list: " + str(drive_data))
        elif robot.get_order_number() >= 6:
            # Discard order if list full
            logging.error("Could not add Order to list. Order discarded")
            client.publish(Topics['BACKEND_DATA_ERROR'], "Could not add Order to list. Order discarded")


def action_driveall(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase,
                    robot: Robot):
    """
    This function is called when the frontend sends a drive_all command which lets the robot drive to all registered plants.
    Same as action_drive(), but for all plants.
    :param client:
    :param userdata:
    :param message:
    :param mydatabase:
    :param robot:
    :return: none
    """

    # Get all plantnames from the database and extract the id from them
    plant_names = mydatabase.get_plant_names()
    plant_ids = []

    for names in plant_names:
        _id = mydatabase.get_plant_id(names[0])
        plant_ids.append(_id)

    # Create a new order number
    action_id = str(uuid.uuid4())
    drive_data = {
        "PlantID": plant_ids,
        "ActionID": action_id
    }

    # Send drive command to Robot if possible (same as action_drive())
    if robot.get_order_number() < 6 and robot.get_robot_status() is True:
        robot.add_order(drive_data)
        client.publish(Topics['ROBOT_ACTION_DRIVEALL'], json.dumps(drive_data))
        logging.info("BACKEND_ACTION_DRIVEALL Drive Command published: " + json.dumps(drive_data))
    else:
        if robot.get_order_number() < 6:
            robot.add_order(drive_data)
            logging.info("BACKEND_ACTION_DRIVEALL New data added to order list: " + str(drive_data))
        elif robot.get_order_number() >= 6:
            client.publish(Topics['BACKEND_DATA_ERROR'], "Could not add Order to list. Order discarded")
            logging.error("Could not add Order to list. Order discarded")


def action_getposition(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase):
    """
    This function is called when the frontend demands the robots position from the backend. It forwards the command to
    the robot.
    :param client: mqtt client object
    :param userdata:
    :param message:
    :param mydatabase:
    :return: none
    """

    # Send command to robot
    client.publish(Topics['ROBOT_ACTION_GETPOSITION'])
    logging.info("BACKEND_ACTION_GETPOSITION message forwarded to Robot")


def action_getbattery(client: mqtt.Client, userdata, message: mqtt.MQTTMessage):
    """
    This function is called when the frontend demands the robots battery status from the backend. It forwards the
    command to the robot to get new information.
    :param client: mqtt client object
    :param userdata:
    :param message:
    :return: none
    """

    # Send command to robot
    client.publish(Topics['ROBOT_ACTION_GETBATTERY'])
    logging.info("BACKEND_ACTION_GETBATTERY message forwarded to Robot")


def action_getalldata(client: mqtt.Client, userdata, message: Union[mqtt.MQTTMessage, list], mydatabase: PlantDataBase):
    """
    This function is called when the frontend demands the last data of the registered plants. It gets the last data from
    the local database and forwards it to the frontend
    :param client: mqtt client object
    :param userdata:
    :param message:
    :param mydatabase: database object, where the plant data is stored
    :return: none
    """

    # get the all PlantNames
    plant_names = mydatabase.get_plant_names()
    alldata = []

    # Get the latest data from all registered plant names by using the plant names
    for i in plant_names:
        alldata.append(mydatabase.get_latest_data(plant_name=i[0]))

    # Send the data as a list to the frontends channel
    client.publish(Topics['BACKEND_DATA_SENSORDATAALL'], json.dumps(alldata))
    logging.info("BACKEND_DATA_SENSORDATAALL got data from database:" + str(alldata))


def action_newplant(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase):
    """
    This function is called when the frontend wants to register a new plant. The information of the new plant is
    delivered from the frontend and used to register the plant
    :param client: mqtt client object
    :param userdata:
    :param message: data from the frontend
    :param mydatabase: local database
    :return: none
    """

    # Load the plant data as json
    plant_data = json.loads(message.payload.decode("UTF-8"))

    # Insert the plant in the database
    mydatabase.insert_plant(plantname=plant_data["PlantName"], plant_id=plant_data["PlantID"])

    # Insert a first measurement value in the database
    mydatabase.insert_measurement_data(plant_id=plant_data["PlantID"],
                                       sensordata_temp=plant_data["AirTemperature"],
                                       sensordata_humidity=plant_data["AirHumidity"],
                                       sensordata_soil_moisture=plant_data["SoilMoisture"],
                                       sensordata_brightness=plant_data["Brightness"])
    logging.info("BACKEND_ACTION_NEWPLANT new plant data received and inserted: " + str(plant_data))

    # Send all new plant data to the frontend to update it
    action_getalldata(client, userdata, message, mydatabase)


def action_configureplant(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase):
    """
    This function is called when a parameter of a plant is changed by the frontend. It updates the information in the
    database and sends the updated data to the frontend
    :param client: mqtt client object
    :param userdata:
    :param message: received data from frontend
    :param mydatabase: local database
    :return: none
    """

    # Load the received data as json
    plant_data = json.loads(message.payload.decode("UTF-8"))

    # Update the plant in the database
    mydatabase.configure_plant(plant_id=plant_data["PlantID"], plantname=plant_data["PlantName"])
    # Insert  measurement_data into the database (from frontend)
    mydatabase.insert_measurement_data(plant_id=plant_data["PlantID"],
                                       sensordata_temp=plant_data["AirTemperature"],
                                       sensordata_humidity=plant_data["AirHumidity"],
                                       sensordata_soil_moisture=plant_data["SoilMoisture"],
                                       sensordata_brightness=plant_data["Brightness"])
    logging.info("BACKEND_ACTION_CONFIGUREPLANT configure plant data received and inserted: " + str(plant_data))

    # Update the frontend with the current data
    action_getalldata(client, userdata, message, mydatabase)


def action_deleteplant(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase):
    """
    This function is called when the frontend wants to delete a registered plant from the database.
    :param client:
    :param userdata:
    :param message: Received data from the frontend
    :param mydatabase: local database object
    :return: none
    """

    # Load the Plant-Name from the message
    delete_plant = json.loads(message.payload.decode("UTF-8"))

    # Delete the plant
    mydatabase.delete_plant(plant_id=delete_plant)
    logging.info("BACKEND_ACTION_DELETEPLANT delete plant data received and deleted: " + str(delete_plant))

    # Send current data to frontend to update it
    action_getalldata(client, userdata, message, mydatabase)


def action_countplants(client: mqtt.Client, userdata, message: mqtt.MQTTMessage, mydatabase: PlantDataBase):
    """
    This function is called when the frontend requires the count of the currently registerd plants. It sends the number
    and maximal possible plant number to the frontend as a json object
    :param client: mqtt client object
    :param userdata:
    :param message:
    :param mydatabase: local database
    :return: none
    """

    # Count plants
    count = mydatabase.plant_count()

    # Create Object and send to the FrontEnd
    count_payload = {
        "CurrentCount": count,
        "MaxCount": MAX_PLANT_COUNT
    }
    client.publish(Topics["BACKEND_DATA_PLANTCOUNT"], json.dumps(count_payload))
    logging.info("BACKEND_DATA_PLANTCOUNT forwarded plant count to FrontEnd: " + str(count_payload))
