import sys
import telnetlib

HOST = "localhost"
PORT = 1235

tn = telnetlib.Telnet(HOST, PORT)

timeout = 0.1
expected = "Welcome"
result = tn.read_until(expected, timeout)

if result == expected:
    print "Success"
else:
    print "Failure"
    sys.exit(1)

print "Sending commands"
tn.write("test\n")
tn.write("exit\n")
