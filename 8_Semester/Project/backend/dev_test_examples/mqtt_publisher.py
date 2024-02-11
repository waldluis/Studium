import paho.mqtt.client as mqtt

import software.backend.defines
from software.backend.defines import MQTT_BROKER_GLOBAL
from random import randrange, uniform
import time
import json
from software.backend.defines import Topics, PLANTDATA
mqttBroker = software.backend.defines.MQTT_BROKER_GLOBAL


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected")
    else:
        print("Connection failed")


client = mqtt.Client()
client.on_connect = on_connect

client.connect(MQTT_BROKER_GLOBAL, 1883)

plantdata = {
    "PlantName": "Ipne"
}


print(type(PLANTDATA))
client.publish(Topics['BACKEND_ACTION_DRIVE'], json.dumps(plantdata))
print(json.dumps(plantdata))
time.sleep(2)
