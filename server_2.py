import socket
import os

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(('127.0.0.1',5005))
server_socket.listen(5)
client_socket, address = server_socket.accept()

exp=1
ACK=1
lost = int(input("Enter the acknowledgement number to be lost : "))
delayed = int(input("Enter the acknowledgement number to be delayed : "))

while 1:
    d=client_socket.recv(1024).decode()
    j,data = d.split(" ")

    if (exp==int(j)):
        print("\nReceived                --> "+str(j)+":"+str(data))
        exp=(exp+1)
        ACK=exp 
        print("Sending Acknowledgement --> "+str(ACK))
        if ACK!=lost:
            client_socket.send(str(ACK).encode())
    else:
        print("Sending Acknowledgement --> "+str(ACK))
        client_socket.send(str(ACK).encode())

    if ACK==delayed:
        print("Sending Acknowledgement --> "+str(ACK))
        client_socket.send(str(ACK).encode())    

server_socket.close ()
