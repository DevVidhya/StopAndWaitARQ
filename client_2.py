import socket, os, time

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
client_socket.settimeout(0.5)
client_socket.connect(('127.0.0.1',5005))

data=1
expected=1

n = int(input("Enter number of words : "))                      
lost = int(input("Enter the frame data number to be lost : "))

while data<=n:
    user_input = input("\nEnter the data to be sent --> ")
    s = str(data)
    print("Sending                   --> " + s + ":" + user_input)
    if data==lost:
        time.sleep(1)
        print("TimeOut")
        time.sleep(2)
        print("Sending                   --> " + s + ":" + user_input)
    client_socket.send(str(s+" "+user_input).encode())
    expected=(expected+1)
    acknowledged = False

    while not acknowledged:
        try:
            ACK = client_socket.recv(1024).decode()
            acknowledged = True
            if expected!=int(ACK):
                print("Discarding the Acknowledgement "+str(ACK))
                acknowledged = False
        except socket.timeout:
            time.sleep(1)
            print("TimeOut")
            time.sleep(2)
            print("Sending                   --> "+s+":"+user_input)
            client_socket.send(str(s+" "+user_input).encode())
    print("Received Acknowledgement  --> "+str(ACK))
    data = data + 1


client_server.close()
