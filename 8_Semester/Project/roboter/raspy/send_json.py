import paho.mqtt.client as mqtt
import random
import time
import json

mqttBroker = "mqtt.eclipseprojects.io"
client1 = mqtt.Client("RobotData")
client1.connect(mqttBroker)

dataDict = {
    "Temperature" : 0,
    "Humidity" : 0
}

while True: 
    dataDict["Temperature"] = random.randint(0, 20)
    dataDict["Humidity"] = random.randint(0, 100)
    client1.publish("Robot/Data", json.dumps(dataDict, indent= 4))
    print("Published " + json.dumps(dataDict) + " to topic Robot/Data")
    time.sleep(5)
