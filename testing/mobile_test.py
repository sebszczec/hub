from lib.test import Test
from lib.mobile import Mobile
from time import sleep
import struct
from collections import namedtuple

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

class MobileHandshakeTest(MobileTest):
    def run(self):
        message = '' 
        message += struct.pack('B', 0)

        for i in range(127):
            message += struct.pack('B', 0)

        self.connection.send(message)
        return True

class MobileUnknownMessageTest(MobileTest):
    def run(self):
        message = '' 
        message += struct.pack('B', 1)

        for i in range(127):
            message += struct.pack('B', 0)

        self.connection.send(message)
        return True
        

