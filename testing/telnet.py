import telnetlib

class Telnet(object):
    def __init__(self, host, port, timeout):
        self.host = host
        self.port = port
        self.timeout = timeout

    def connect(self):
        self.connection = telnetlib.Telnet(self.host, self.port)

    def close(self):
        self.connection.close()

    def expect(self, message):
        if message == self.connection.read_until(message, self.timeout):
            return True
        else:
            return False

    def send(self, message):
        message = message + "\n"
        self.connection.write(message)
