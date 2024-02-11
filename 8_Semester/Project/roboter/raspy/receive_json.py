import paho.mqtt.client as mqtt
import json


def on_message_json(client, userdata, message):
    strIn = str(message.payload.decode("UTF-8"))
    dataDict = json.loads(strIn)
    print("Received data: ", type(dataDict))


mqttBroker = "mqtt.eclipseprojects.io"
client = mqtt.Client("Smartphone_temp")

dataDict = {}

client.message_callback_add("Robot/Data", on_message_json)

client.connect(mqttBroker)
client.subscribe("Robot/Data")

client.loop_forever()
