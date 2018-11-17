from lib.test import Test
from lib.mobile import Mobile
from mobile_messages_pb2 import *
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
        message = HandshakeRequest()
        message.messageId = 0
        self.connection.send(message.SerializeToString())
        return True

class MobileUnknownMessageTest(MobileTest):
    def run(self):
        message = HandshakeRequest()
        message.messageId = 99
        self.connection.send(message.SerializeToString())
        return True

        

