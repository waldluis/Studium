import random

from plantdatabase import PlantDataBase

mydatabase = PlantDataBase('backend_database.db')
mydatabase.create_tables()

for i in range(1, 6):
    mydatabase.insert_plant(plantname=f"Pflanze{i}")

for i in range(1, 7):
    plant_id = i
    temp = random.random()
    humidity = random.random()
    soil_moisture = random.random()
    light_intensity = random.random()
    mydatabase.insert_measurement_data(plant_id=plant_id,
                                       sensordata_temp=temp,
                                       sensordata_humidity=humidity,
                                       sensordata_soil_moisture=soil_moisture,
                                       sensordata_brightness=light_intensity)
