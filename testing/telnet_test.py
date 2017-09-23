from lib.test import Test
from lib.telnet import Telnet

# Base class for all telnet tests
class TelnetTest(Test):
    def setup(self):
        self.connection = Telnet("localhost", 1235, 0.1)
        self.connection.connect()
        return True

    def run(self):
        raise NotImplementedError("Subclass must implement abstract method")

    def teardown(self):
        self.connection.close()
        return True

class TelnetConnectionTest(TelnetTest):
    def run(self):
        Test.run(self)
        result = self.connection.expect(["Welcome"])
        return result

class TelnetTalkWithOtherSessionTest(TelnetTest):
    def run(self):
        Test.run(self)
        connection2 = Telnet("localhost", 1235, 0.1)
        connection2.connect()
        connection2.expect(["Welcome"])
        message1 = "MESSAGE1"
        message2 = "MESSAGE2"
        
        connection2.send(message1)
        result1 = self.connection.expect([message1])
        
        self.connection.send(message2)
        result2 = connection2.expect([message2])
        
        connection2.close()
        return result1 and result2

class TelnetNotReadingTest(TelnetTest):
    def run(self):
        Test.run(self)
        message = "MESSAGE"
        self.connection.send(message)
