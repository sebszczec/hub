from lib.test import Test
from lib.telnet import Telnet

class TelnetTest(Test):
    def __init__(self, name):
        Test.__init__(self, name)
        self.connection = Telnet("localhost", 1235, 0.1)

    def run(self):
        Test.run(self)
        self.connection.connect()
        result = self.connection.expect("Welcome")
        self.connection.close()
        return result
