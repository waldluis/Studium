import paho.mqtt.client as mqtt
import random
import time

mqttBroker = "mqtt.eclipseprojects.io"
client1 = mqtt.Client("Temperature")
client1.connect(mqttBroker)

while True: 
    randNumber = random.randint(0, 20)
    client1.publish("TEMPERATURE", randNumber)
    print("Published " + str(randNumber) + " to topic TEMPERATURE")
    time.sleep(2)

    randNumber = random.randint(0, 100)
    client1.publish("HUMIDITY", randNumber)
    print("Published " + str(randNumber) + " to topic HUMIDITY")
    time.sleep(2)