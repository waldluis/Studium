"""
created by waldhauser

This file contains the functions to read the sensors DHT22, TSL2561, earth humidity with MCP3008 ADC and RaspberryPi camera 
Every sensor can be read on its own
Reading all sensors is possible with the readSensors() function and provides the data in the format of SENSORDATA dictionary
"""

import adafruit_dht
import adafruit_tsl2561
import board
import spidev
from picamera import PiCamera
from defines import SENSORDATA


def readDHT22(): 
    """
    Reads DHT22 air temperature and air humidity and return values as float

    Raises:
        Exception: If DHT22 not connected properly

    Returns:
        float: temperature [°C]
        float: humidity [%]
    """
    try:
        dht22 = adafruit_dht.DHT22(board.D4, use_pulseio=False)
    except:
        raise Exception("DHT22 not connected")
    
    # read DHT22
    try:
        temperature = dht22.temperature
        humidity = dht22.humidity
    except:
        raise Exception("DHT22 not connected")

    return temperature, humidity


def readTSL2561():
    """
    Reads TSL2561 brightness via I2C in Lux and returns integer value

    Raises:
        Exception: If TSL2561 not connected properly

    Returns:
        int: brightness [Lux]
    """
    try:
        tsl2561 = adafruit_tsl2561.TSL2561(board.I2C())
    except:
        raise Exception("TSL2561 not connected")
    
    # read TSL2561
    brightness = 0
    if type(tsl2561.lux) == type(None):  # Max Value 40.000 -> above error
        brightness = 40000
    else:
        brightness = int(tsl2561.lux)

    return brightness


def readMCP3008():
    """
    Reads YL-69 via MCP3008 ADC and SPI soil moisture in percent and returns float value
    
    Raises:
        Exception: If YL-69 not connected properly

    Returns:
        float: soil moisture [%]
    """

    channel = 0                                         # Input channel into MCP3008 ADC
    try:
        spi = spidev.SpiDev()
        spi.open(0,0)
        spi.max_speed_hz = 1000000
    except:
        raise Exception("YL69 not connected")

    val = spi.xfer2([1,(8+channel) << 4, 0])
    data = ((val[1] & 3) << 9) +val[2]
    percentage = data - 680                             # Return values between ~1780 and ~680
    percentage = round(((1100 - percentage) / 1100) *100, 2)   # 680 -> 100% moisture, 1780 -> 0% moisture

    if percentage > 100 or percentage < 0:                # If not connected values above 100% appear  
        raise Exception("YL69 not connected")

    return percentage


def readSensors(sensorData):
    """
    Read DHT22, TSL2561 and Humidity Sensor
    Dictionary is passed to ensure that values are available when errors occur
    When error occurs during reading of sensor, affected values are set to 0

    Args:
        sensorData (dictionary): Dictionary of type SENSORDATA

    Raises:
        Exception: DHT22 not connected
        Exception: TSL2561 not connected
        Exception: YL69 not connected
    """
    errorMessage = ""

    # read DHT22
    try:
        sensorData["AirTemperature"], sensorData["AirHumidity"] = readDHT22()   
    except Exception as e:
        sensorData["AirHumidity"] = 0                   # No value returend if error occurs -> setting safe values
        sensorData["AirTemperature"] = 0
        errorMessage = str(e) + "\n"                    # Appending received error message to later forward all occured errors

    # read TSL2561
    try:
        sensorData["Brightness"] = readTSL2561()
    except Exception as e:
        sensorData["Brightness"] = 0                   # No value returend if error occurs -> setting safe value
        errorMessage = errorMessage + str(e) + "\n"    # Appending received error message to later forward all occured errors

    # read YL-69
    try:
        sensorData["SoilMoisture"] = readMCP3008()
    except Exception as e:
        sensorData["SoilMoisture"] = 0                 # No value returend if error occurs -> setting safe value
        errorMessage = errorMessage + str(e) + "\n"    # Appending received error message to later forward all occured errors

    # raise combined error message, successfull values still available
    if errorMessage != "":
        raise Exception(errorMessage)
    


def takePicture():
    """
    Take picture and store as "picture.png" in current folder

    """
    try:
        camera = PiCamera()
    except:
        raise Exception("Camera not connected")
    
    camera.start_preview()
    camera.capture("picture.png")
    camera.stop_preview()


def readPosition():
    """
    Read and return Position

    ***Not implemented, available GPS-sensor was not working***

    Returns:
        _type_: _description_
     """
    position = ""
    return position


# Testing
def main():
    value = SENSORDATA
    try:
        readSensors(value)
    except Exception as e:
        print(str(e))

    print(value)

if __name__ == "__main__":
    main()