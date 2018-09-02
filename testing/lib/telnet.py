import telnetlib
from network import NetworkClient
import time

class Telnet(object):
    def __init__(self, host, port, timeout):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.connection = None

    def connect(self):
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
