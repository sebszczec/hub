#!/usr/bin/expect
set timeout 50
spawn telnet localhost 1235
expect "Welcome"
send -- "Test message1\r"
sleep 0.1
send -- "\35\r"
expect "telnet>"
send -- "close\r" 

