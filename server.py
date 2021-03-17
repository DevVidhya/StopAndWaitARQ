import socket
import os

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(('192.168.43.39',5005))
server_socket.listen(5)

client_socket, address = server_socket.accept()
i=0
ACK="NIL"
while 1:
    d=client_socket.recv(1024).decode()
    j,data = d.split(" ")
    print(j)
    if (i==int(j)):
        print("Received --> "+data)
        ACK="Acknowledgement: Message Received"
        i = i + 1
        client_socket.send(ACK.encode())
    else:
        client_socket.send(ACK.encode())
server_socket.close ()
