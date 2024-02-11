class Robot:
    """
    This class contains the features of the robot. It is used as an interface for the main to avoid global variables and
    store them instead an instance of this robot object. It saves the orders and some basic information of the robots status
    """
    def __init__(self):
        self.robot_ready = True
        self.order_handler = []
        self.battery = 0
        self.position = ""
        self.last_error = ""

    def change_robot_status(self, status: bool):
        self.robot_ready = status

    def add_order(self, drivedata):
        self.order_handler.append(drivedata)

    def delete_order(self, drivedata):
        self.order_handler.remove(drivedata)

    def get_next_order(self):
        return self.order_handler[0]

    def get_order_number(self):
        return len(self.order_handler)

    def store_battery(self, battery):
        self.battery = battery

    def store_position(self, position):
        self.position = position

    def store_last_error(self, error):
        self.last_error = error

    def get_battery(self):
        return self.battery

    def get_position(self):
        return self.position

    def get_last_error(self):
        return self.last_error

    def get_robot_status(self):
        return self.robot_ready
