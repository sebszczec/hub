import socket, ssl
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
        
class SSLClient(NetworkClient):
    def __init__(self, address, port):
        NetworkClient.__init__(self, address, port)

        self.context = ssl.SSLContext(ssl.PROTOCOL_SSLv23)
        self.context.verify_mode = ssl.CERT_NONE
        self.context.check_hostname = False
        self.context.load_default_certs()
        self.ssl_sock = self.context.wrap_socket(self.sock, server_hostname=self.address)

    def connect(self):
        self.ssl_sock.connect((self.address, self.port))

    def disconnect(self):
        self.ssl_sock.close()
        NetworkClient.disconnect(self)

    def send_data(self, data):
        self.ssl_sock.send(data)

    def receive_data(self, size):
        chunks = []
        bytes_recd = 0
        while bytes_recd < size:
            chunk = self.ssl_sock.recv(min(size - bytes_recd, 2048))
            if chunk == b'':
                raise RuntimeError("SSL socket connection broken")
            
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)

            if chunk == '\n':
                break

        return b''.join(chunks)