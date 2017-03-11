import sys
from testing.lib.telnet import Telnet

telnet = Telnet("localhost", 1235, 0.1)
telnet.connect()

if telnet.expect("Welcome"):
    print "Success"

telnet.close()