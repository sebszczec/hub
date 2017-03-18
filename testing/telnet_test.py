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

class TelnetUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".uptime")
        result = self.connection.expect([r"[0-9]+ hours, [0-9]+ minutes, [0-9]+ seconds, [0-9]+ milliseconds"])
        return result

