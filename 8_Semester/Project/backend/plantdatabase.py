# file to create a database via python script
import sqlite3
from typing import Optional
import logging


class PlantDataBase:
    """
    Class of a PlantDataBase Object. It contains functions specifically for the plantdatabase.
    Usage:
    - First declare object
    - Then use create_tables() to create the tables (NECESSARY !!)
    - After that use the methods of this class
    """

    def __init__(self, database_name: str):
        """
        Only Constructor of the Class. Pass name of database to connect to. If not available it will create a new one.
        :param database_name: Name of the SQLITE database file system
        """
        self.db_file = database_name  # 'backend_database.db' usually used name
        self.conn = None
        try:
            # connect or create new database if not available
            self.conn = sqlite3.connect(self.db_file, check_same_thread=False)
        except sqlite3.Error as e:
            logging.error("Database init error: " + str(e))

        # cursor on the database
        self.cur = self.conn.cursor()

    def create_tables(self):
        """
        Use this method to create the plants and measurement_values tables. Call this function before using the data
        handling methods below
        :return: True if successfully, False if not
        """
        try:
            # Create plants table if not already existing
            table_config = "CREATE TABLE IF NOT EXISTS plants " \
                           "(PlantID INTEGER PRIMARY KEY," \
                           "PlantName TEXT)"
            self.cur.execute(table_config)

            # Create measurement_values_table if not already existing
            table_config = "CREATE TABLE IF NOT EXISTS measurement_values " \
                           "(measurementID INTEGER PRIMARY KEY," \
                           "Timestamp DATETIME DEFAULT (datetime('now', 'localtime'))," \
                           "PlantID INTEGER, " \
                           "AirTemperature REAL," \
                           "AirHumidity REAL," \
                           "SoilMoisture REAL," \
                           "Brightness REAL," \
                           "FOREIGN KEY (PlantID)" \
                           "REFERENCES plants (PlantID) )"
            self.cur.execute(table_config)
            return True
        except sqlite3.Warning as e:
            logging.error("Could not create tables: " + str(e))
            return False

    def insert_plant(self, plantname: str, plant_id: int) -> bool:
        """
        Insert a new plant with an id and a plantname
        :param plantname: name of plant
        :param plant_id: id of plant (position in the bed, must be unique!!)
        :return: True if successfully, False if not
        """
        try:
            self.cur.execute("INSERT INTO plants (PlantName, PlantID) VALUES (?,?)", (plantname, plant_id))
            self.conn.commit()
            return True
        except Exception as e:
            logging.error("Could not insert plant: " + str(e))
            return False

    def configure_plant(self, plant_id: int, plantname: str) -> bool:
        """
        Change a plants parameters in the database by using its PlantID as a search criteria
        :param plant_id: id of plant
        :param plantname: name of plant
        :return: True if successfully, False if not
        """
        try:
            self.cur.execute("UPDATE plants SET PlantID = ?, PlantName = ? WHERE PlantID= ?",
                             (plant_id, plantname, plant_id))
            self.conn.commit()
            return True
        except Exception as e:
            logging.error("Could not configure plant: " + str(e))
            return False

    def delete_plant(self, plant_id):
        """
        Delete a plant from the database
        :param plant_id: PlantID of plant to delete
        :return: True if successfully, False if not
        """
        try:
            self.cur.execute('DELETE FROM plants WHERE PlantID = ?', (plant_id,))
            self.conn.commit()
            return True
        except Exception as e:
            logging.error("Could not delete plant: " + str(e))
            return False

    def insert_measurement_data(self, plant_id,
                                sensordata_temp,
                                sensordata_humidity,
                                sensordata_soil_moisture,
                                sensordata_brightness) -> bool:
        """
        Insert a measurement value of plantID
        :param plant_id: plantID of plant
        :param sensordata_temp: Temperature
        :param sensordata_humidity: Air Humidity value
        :param sensordata_soil_moisture: Soil Moisture value
        :param sensordata_brightness: brightness value
        :return: True if successfully, False if not
        """
        try:
            self.cur.execute(f"INSERT INTO measurement_values (PlantID, AirTemperature, AirHumidity,"
                            f"SoilMoisture, Brightness) VALUES "
                            f"({plant_id}, {sensordata_temp}, {sensordata_humidity}, {sensordata_soil_moisture}"
                            f", {sensordata_brightness})")
            self.conn.commit()
            return True
        except Exception as e:
            logging.error("Could not insert measurement data: " + str(e))
            return False

    def get_latest_data(self, plant_name: Optional[str] = None, plant_id: Optional[int] = None):
        """
        Gets the newest parameter of specific plant and returns all parameters in json format.
        Either pass plant_name OR plant_id, BOTH passed -> ERROR
        :param plant_id: PlantID of plant
        :param plant_name: Name of Plant
        :return: JSON with data if successfully, else none
        """
        try:
            if plant_name is not None and plant_id is None:
                self.cur.execute("SELECT PlantID FROM plants where PlantName = ?", (plant_name,))
                plant_id = self.cur.fetchone()[0]
            elif (plant_id is not None and plant_name is not None) or (plant_id is None and plant_name is None):
                raise TypeError("Can't pass plant_id and plant_name to the function. Just one allowed !")

            self.cur.execute("SELECT * FROM measurement_values where PlantID = ? ORDER BY Timestamp DESC LIMIT 1",
                             (plant_id,))
            data = self.cur.fetchone()
            json_file = {
                "MeasurementID": data[0],
                "PlantID": data[2],
                "Timestamp": data[1],
                "AirTemperature": data[3],
                "AirHumidity": data[4],
                "SoilMoisture": data[5],
                "Brightness": data[6],
                "PlantName": plant_name
            }
            return json_file

        except Exception as e:
            logging.error("Could not get measurement values: " + str(e))

    def delete_data(self, table_name):
        """
        Delete all data from a specific tabel
        :param table_name: tabel you want to delete
        :return: True if successfully, False if not
        """
        try:
            self.cur.execute(f'DELETE FROM {table_name}')
            self.conn.commit()
            return True
        except Exception as e:
            logging.error("Could not delete data: " + str(e))

    def plant_count(self) -> int:
        """
        returns the number of plants registered in the database
        :return: Count of registered plants as int
        """
        try:
            self.cur.execute("SELECT COUNT(*) FROM plants")
            return self.cur.fetchone()[0]
        except Exception as e:
            logging.error("Could not count plants: " + str(e))

    def get_plant_names(self) -> list:
        """
        Use this method to get a list of the Names of all registered plants
        :return: list containing plantNames
        """
        try:
            self.cur.execute("SELECT PlantName FROM plants")
            return self.cur.fetchall()
        except Exception as e:
            logging.error("Could not get plant names: " + str(e))

    def get_plant_id(self, plant_name: str) -> int:
        """
        Use this method to get the PlantID of a registered plant by its name
        :param plant_name: name of registered plant
        :return: ID of plant as int
        """
        try:
            self.cur.execute("SELECT PlantID FROM plants WHERE PlantName=?", (plant_name,))
            return self.cur.fetchone()[0]
        except Exception as e:
            logging.error("Could not get plant id: " + str(e))

    def __del__(self):
        """
        Destructor of Class. Disconnects from database.
        """
        self.conn.close()
