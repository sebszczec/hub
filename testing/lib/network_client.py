import socket
import sys

class NetworkClient(object):
    def __init__(self, adderss, port):
        self.address = adderss
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    def connect(self):
        server_address = (self.address, self.port)
        self.sock.connect(server_address)

    def disconnect(self):
        self.sock.shutdown(SHUT_RDWR)
        self.sock.close()

    def send_data(self, data):
        self.sock.sendall(data)

    def receive_data(self):
        data = self.sock.recv(1024)
        return data
        
