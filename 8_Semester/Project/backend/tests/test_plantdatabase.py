#
# created by caliskan
# use this file to test your plantdatabase changes

from software.backend.plantdatabase import PlantDataBase
import pytest


def test_create_table():
    testdatabase = PlantDataBase(database_name='test_database.db')
    assert testdatabase.create_tables() is True


def test_insert_and_delete_plant():
    testdatabase = PlantDataBase(database_name='test_database.db')

    assert testdatabase.create_tables() is True
    assert testdatabase.delete_data("plants") is True
    assert testdatabase.insert_plant(plantname="Bertha", plant_id=1) is True
    assert testdatabase.plant_count() == 1
    assert testdatabase.delete_plant(plant_id=1) is True
    assert testdatabase.plant_count() == 0


def test_insert_and_get_measurement_values():
    test_plant_id = 2
    test_temp = 22.4
    test_humidity = 93.4
    test_soil_moisture = 12.5
    test_brightness = 66
    test_plant_name = "Bertha"

    testdatabase = PlantDataBase(database_name='test_database.db')
    assert testdatabase.create_tables() is True
    assert testdatabase.delete_data("plants") is True
    assert testdatabase.insert_plant(plantname=test_plant_name, plant_id=test_plant_id) is True

    assert testdatabase.insert_measurement_data(plant_id=test_plant_id,
                                                sensordata_temp=test_temp,
                                                sensordata_humidity=test_humidity,
                                                sensordata_soil_moisture=test_soil_moisture,
                                                sensordata_brightness=test_brightness) is True
    test_plant_data = testdatabase.get_latest_data(plant_name=test_plant_name)
    print(test_plant_data)
    assert test_plant_data["PlantID"] == test_plant_id
    assert test_plant_data["AirTemperature"] == test_temp
    assert test_plant_data["AirHumidity"] == test_humidity
    assert test_plant_data["SoilMoisture"] == test_soil_moisture
    assert test_plant_data["Brightness"] == test_brightness
    assert test_plant_data["PlantName"] == test_plant_name
