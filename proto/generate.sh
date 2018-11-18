#!/bin/bash
protoc --cpp_out=. --python_out=. mobile_messages.proto
cp mobile_messages.pb.* ../src/network
cp mobile_messages.pb2.py ../testing

