#!/bin/bash
protoc --cpp_out=. --python_out=. mobile_messages.proto
