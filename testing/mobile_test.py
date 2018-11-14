from lib.test import Test
from lib.mobile import Mobile
from time import sleep

# Base class for all mobile tests
class MobileTest(Test):
    def setup(self):
        self.connection = Mobile()
        self.connection.connect()
        return True

    def run(self):
        raise NotImplementedError("Subclass must implement abstract method")

    def teardown(self):
        self.connection.close()
        return True

class MobileConnectionTest(MobileTest):
    def run(self):
        return Test.run(self)
