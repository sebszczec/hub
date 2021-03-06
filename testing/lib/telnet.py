import telnetlib
from network import *
from environment import Environment
import time

class Telnet(object):
    def __init__(self):
        self.host = Environment.host

        if (Environment.use_ssl == True):
            self.port = Environment.ssl_port
        else:
            self.port = Environment.telnet_port
        
        self.timeout = Environment.telnet_timeout
        self.connection = None

    def connect(self):
        if (Environment.use_ssl == True):
            self.network_connection = SSLClient(self.host, self.port)
        else:
            self.network_connection = NetworkClient(self.host, self.port)
        
        self.network_connection.connect()

    def close(self):
        self.network_connection.disconnect()

    def expect(self, message):
        data = None
        data = self.network_connection.receive_data(len(message))

        # removing last characters
        received = data[:-1]
        expected = message[:-1]

        if expected.find(received) != -1:
            return True
        else:
            print "Expected: " +  str(len(message)) + " " + message
            print "Got: " +  str(len(data)) + " " + data.decode()
            return False


    def send(self, message):
        message = message + "\r"
        self.network_connection.send_data(message)
