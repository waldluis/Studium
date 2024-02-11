import paho.mqtt.client as mqtt
import time
from software.backend.defines import Topics
from software.backend.defines import MQTT_BROKER_GLOBAL


def on_message(client, userdata, message):
    print("received message: ", str(message.payload.decode("utf-8")))


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected")
    else:
        print("Connection failed")


mqttBroker = ""

client = mqtt.Client()
client.connect(MQTT_BROKER_GLOBAL, 1883)

client.on_message = on_message

client.subscribe(Topics['BACKEND_ACTION_GETALLDATA'])
client.loop_forever()
