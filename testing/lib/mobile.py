import telnetlib
from network import *
from environment import Environment
import time

class Mobile(object):
    def __init__(self):
        self.host = Environment.host
        self.port = Environment.mobile_port
        self.connection = None

    def connect(self):
        self.network_connection = NetworkClient(self.host, self.port)
        self.network_connection.connect()

    def close(self):
        self.network_connection.disconnect()

    def expect(self, message):
        return False

    def send(self, message):
        return False
