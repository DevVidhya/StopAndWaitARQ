import socket
import os

# creating receiver socket which uses TCP in transport layer
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# binding the server socket to IP address
server_socket.bind(('127.0.0.1',5005))

# receiver listens on port 5005
server_socket.listen(5)

# receiver accepts connection from sender
client_socket, address = server_socket.accept()

# initialising expected frame number and ack no.
exp=1
ACK=1

# randomly selecting acknowledgement to be dropped or damaged in channel
lost = int(input("Enter the acknowledgement number to be lost : "))

# randomly selecting acknowledgement to be delayed in channel
delayed = int(input("Enter the acknowledgement number to be delayed : "))

# Receiver listens till sender terminates the connection
while 1:
    # Receiver receives data from sender
    d=client_socket.recv(1024).decode()
    j,data = d.split(" ")

    # accepting the frame if expected seq no is same as the one received and sending acknowledgement with next expected frame no
    # if duplicate frames received discard it and resend the previous ack (i.e. the expected frame)
    if (exp==int(j)):
        print("\nReceived                --> "+str(j)+":"+str(data))
        exp=(exp+1)
        ACK=exp 
        if ACK==(delayed+1):
            client_socket.send(str(delayed).encode())
        print("Sending Acknowledgement --> "+str(ACK))
        if (ACK!=lost) and (ACK!=delayed):
            client_socket.send(str(ACK).encode())
    else:
        print("Sending Acknowledgement --> "+str(ACK))
        client_socket.send(str(ACK).encode())

server_socket.close ()
