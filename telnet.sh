#!/usr/bin/expect
set timeout 10
spawn telnet localhost 1235
expect "Welcome"
send "Test message1\n\r"
send "Test message2\n\r"
sleep 1
