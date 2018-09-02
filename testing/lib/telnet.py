import telnetlib
from network import NetworkClient

class Telnet(object):
    def __init__(self, host, port, timeout):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.connection = None
        #self.network_connection = None

    def connect(self):
        self.connection = telnetlib.Telnet(self.host, self.port)
        #self.network_connection = NetworkClient(self.host, self.port)
        #self.network_connection.connect()

    def close(self):
        self.connection.close()
        #self.network_connection.disconnect()

    def expect(self, message):
        index, mo, response = self.connection.expect(message, self.timeout)
        if index == -1:
            return False
        else:
            return True

        #data = self.network_connection.receive_data()


    def send(self, message):
        message = message + "\r"
        self.connection.write(message)
        #self.network_connection.send_data(message)
