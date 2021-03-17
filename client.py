import socket, os
from threading import *

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
client_socket.settimeout(0.5)
client_socket.connect(('192.168.43.39',5005))

user_input= input("Data entry --> ")
i=0
while user_input:
    s = str(i) + " " + user_input
    client_socket.send(s.encode())  
    print("Data sent -->" + user_input)
    acknowledged = False
    while not acknowledged:
        try:
            ACK = client_socket.recv(1024).decode()
            acknowledged = True
            i=i+1
        except socket.timeout:
            client_socket.send(s.encode())
    print(ACK)
    user_input = input("Data entry --> ")
client_server.close()
