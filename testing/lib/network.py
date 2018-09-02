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
        #self.sock.shutdown(0)
        self.sock.close()

    def send_data(self, data):
        self.sock.send(data)

    def receive_data(self, size):
        chunks = []
        bytes_recd = 0
        while bytes_recd < size:
            chunk = self.sock.recv(min(size - bytes_recd, 2048))
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)

            if chunk == '\n':
                break

        return b''.join(chunks)
        
