from lib.test import Test
from lib.telnet import Telnet
from time import sleep

# Base class for all telnet tests
class TelnetTest(Test):
    def setup(self):
        self.connection = Telnet()
        self.connection.connect()
        result = self.connection.expect("Welcome\n")
        return result

    def run(self):
        raise NotImplementedError("Subclass must implement abstract method")

    def teardown(self):
        self.connection.close()
        return True

class TelnetConnectionTest(TelnetTest):
    def run(self):
        return Test.run(self)

class TelnetTalkWithOtherSessionTest(TelnetTest):
    def run(self):
        Test.run(self)
        
        connection2 = Telnet()
        connection2.connect()
        connection2.expect("Welcome\n")
        message1 = "MESSAGE1"
        message2 = "MESSAGE2"
        
        connection2.send(message1)
        result1 = self.connection.expect(message1 + "\r")
        
        self.connection.send(message2)
        result2 = connection2.expect(message2 + "\r")
        
        connection2.close()
        return result1 and result2

class TelnetNotReadingTest(TelnetTest):
    def run(self):
        Test.run(self)
        message = "MESSAGE"
        self.connection.send(message)
        self.connection.close()
        sleep(0.05)
