import paho.mqtt.client as mqtt


def on_message_temp(client, userdata, message):
    print("Received temp message: ", str(message.payload.decode("utf-8")))

def on_message_hum(client, userdata, message):
    print("Received hum message: ", str(message.payload.decode("utf-8")))
    

mqttBroker = "mqtt.eclipseprojects.io"
client = mqtt.Client("Smartphone_temp")

client.message_callback_add("TEMPERATURE", on_message_temp)
client.message_callback_add("HUMIDITY", on_message_hum)

client.connect(mqttBroker)
client.subscribe("TEMPERATURE")
client.subscribe("HUMIDITY")

client.loop_forever()