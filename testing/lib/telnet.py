import telnetlib

class Telnet(object):
    def __init__(self, host, port, timeout):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.connection = None

    def connect(self):
        self.connection = telnetlib.Telnet(self.host, self.port)

    def close(self):
        self.connection.close()

    def expect(self, message):
        index, mo, response = self.connection.expect(message, self.timeout)
        if index == -1:
            return False
        else:
            return True

    def send(self, message):
        message = message + "\r"
        self.connection.write(message)
