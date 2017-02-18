#!/usr/bin/expect
set timeout 10
spawn telnet localhost 1235
expect "Welcome"
send "Test message1\r"
send "Test message2\r"
sleep 1
