from lib.test import Test
from lib.telnet import Telnet

class TelnetTest(Test):
    def run(self):
        Test.run(self)
        connection = Telnet("localhost", 1235, 0.1)
        connection.connect()
        result = connection.expect("Welcome")
        connection.close()
        return result
