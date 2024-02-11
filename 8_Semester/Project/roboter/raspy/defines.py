"""
created by caliskan at 19.04.2023

contains all constants for the backend architecture of the smart garden project
"""

MQTT_BROKER_LOCAL = "192.168.0.199"
MQTT_BROKER_GLOBAL = "mqtt.eclipseprojects.io"
RASPI_CLIENT_ID = "smart_farming_raspi"
BACKEND_CLIENT_ID = "smart_farming_server"
MAX_PLANT_COUNT = 6
DATABASE_NAME = 'backend_database.db'

# Topics:
Topics = {
    "ROBOT_ACTION_DRIVE": "ROBOT/ACTION/DRIVE",
    "ROBOT_ACTION_DRIVEALL": "ROBOT/ACTION/DRIVEALL",
    "ROBOT_ACTION_GETPOSITION": "ROBOT/ACTION/GETPOSITION",
    "ROBOT_ACTION_GETBATTERY": "ROBOT/ACTION/GETBATTERY",

    "ROBOT_DATA_SENSORDATA": "ROBOT/DATA/SENSORDATA",
    "ROBOT_DATA_BATTERY": "ROBOT/DATA/BATTERY",
    "ROBOT_DATA_POSITION": "ROBOT/DATA/POSITION",
    "ROBOT_DATA_PICTURE": "ROBOT/DATA/PICTURE",
    "ROBOT_DATA_ERROR": "ROBOT/DATA/ERROR",
    "ROBOT_DATA_ROBOTREADY": "ROBOT/DATA/ROBOTREADY",
    "ROBOT_DATA_ALL": "ROBOT/DATA/ALL",

    "BACKEND_ACTION_DRIVE": "BACKEND/ACTION/DRIVE",
    "BACKEND_ACTION_DRIVEALL": "BACKEND/ACTION/DRIVEALL",
    "BACKEND_ACTION_GETPOSITION": "BACKEND/ACTION/GETPOSITION",
    "BACKEND_ACTION_GETBATTERY": "BACKEND/ACTION/GETBATTERY",
    "BACKEND_ACTION_GETALLDATA": "BACKEND/ACTION/GETALLDATA",
    "BACKEND_ACTION_NEWPLANT": "BACKEND/ACTION/NEWPLANT",
    "BACKEND_ACTION_CONFIGUREPLANT": "BACKEND/ACTION/CONFIGUREPLANT",
    "BACKEND_ACTION_DELETEPLANT": "BACKEND/ACTION/DELETEPLANT",
    "BACKEND_ACTION_PLANTCOUNT": "BACKEND/ACTION/PLANTCOUNT",

    "BACKEND_DATA_SENSORDATA": "BACKEND/DATA/SENSORDATA",
    "BACKEND_DATA_SENSORDATAALL": "BACKEND/DATA/SENSORDATA_ALL",
    "BACKEND_DATA_POSITION": "BACKEND/DATA/POSITION",
    "BACKEND_DATA_BATTERY": "BACKEND/DATA/BATTERY",
    "BACKEND_DATA_PICTURE": "BACKEND/DATA/PICTURE",
    "BACKEND_DATA_PLANTCOUNT": "BACKEND/DATA/PLANTCOUNT",
    "BACKEND_DATA_ERROR": "BACKEND/DATA/ERROR",
    "BACKEND_DATA_ROBOTREADY": "BACKEND/DATA/ROBOTREADY"

}

# MQTT Messages:

# region Robot -> Backend
SENSORDATA = {
    "AirTemperature": 0.0,
    "AirHumidity": 0.0,
    "SoilMoisture": 0.0,
    "Brightness": 0,
    "PlantID": 0,
    "ActionID": ""
}

ALLSENSORDATA = {
    "SensorData": [],
    "ActionID": ""
}

POSITION = {
    "Position": ""
}

BATTERY = {
    "Battery": 0.0
}

# endregion

# region Backend -> Robot

DRIVE = {
    "PlantID": 0,
    "ActionID": ""
}

DRIVEALL = {
    "PlantID": [0, 0],  # List containing PlantIDs sorted ascending
    "ActionID": ""
}
# GETPOSITION -> no message needed

# GETBATTERY -> no message needed

# endregion

# region Backend -> Frontend

PLANTDATA = {
    "AirTemperature": 0.0,
    "AirHumidity": 0.0,
    "SoilMoisture": 0.0,
    "Brightness": 0,
    "PlantID": 0,
    "Timestamp": "",
    "MeasurementID": 0,
    "PlantName": ""
}

ALLPLANTDATA = [
    PLANTDATA,
    PLANTDATA,
    PLANTDATA,
    PLANTDATA,
    PLANTDATA,
    PLANTDATA
]

POSITION = {
    "Position": "",
    "Timestamp": ""
}

BATTERY = {
    "Battery": 0.0,
    "Timestamp": ""
}

PLANTCOUNT = {
    "CurrenCount": 0,
    "MaxCount": 0
}

# endregion

# region Frontend -> Backend

DRIVE = {
    "PlantName": ""
}

NEWPLANT = PLANTDATA

CONFIGUREPLANT = PLANTDATA

DELETEPLANT = {
    "PlantID": ""
}

# DRIVEALL -> no message needed

# GETPOSITION -> no message needed

# GETBATTERY -> no message needed

GETALLDATA = {
    "PlantNames": []
}

# endregion
