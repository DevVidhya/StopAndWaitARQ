import socket, os, time

# creating a sender socket which uses TCP in transport layer
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

client_socket.settimeout(0.5)

# connecting to the sender at port 5005
client_socket.connect(('127.0.0.1',5005))

# seq number of sending data frame and ack no received from the receiver initialised to 1
data=1
expected=1

# taking input from network layer for no of frames to be sent(1 word per frame)
n = int(input("Enter number of words : "))      
# randomly selecting frame to be dropped or damaged in channel                          
lost = int(input("Enter the frame data number to be lost : "))

# sending to receiver n frames
while data<=n:
    # getting each frame
    user_input = input("\nEnter the data to be sent --> ")
    s = str(data)
 
    print("Sending                   --> " + s + ":" + user_input)
    # handling corrupted or lost data frames
    # if timeout occurs then frame is resent
    if data==lost:
        time.sleep(1)
        print("TimeOut")
        time.sleep(2)
        print("Sending                   --> " + s + ":" + user_input)

    # sending the data frame
    client_socket.send(str(s+" "+user_input).encode())
    expected=(expected+1)
    acknowledged = False

    # handling lost acknowledgement
    # if acknowlegement not received before timeout, frame is resent
    while not acknowledged:
        # receiving acknowledgement if not lost
        try:
            ACK = client_socket.recv(1024).decode()
            acknowledged = True
            if expected!=int(ACK):
                print("Discarding the Acknowledgement "+str(ACK))
                acknowledged = False
        # resending frame if acknowledgement is lost
        except socket.timeout:
            time.sleep(1)
            print("TimeOut")
            time.sleep(2)
            print("Sending                   --> "+s+":"+user_input)
            # resending frame for lost acknowledgement
            client_socket.send(str(s+" "+user_input).encode())
    print("Received Acknowledgement  --> "+str(ACK))
 
    # incrementing sequence number
    data = data + 1


client_server.close()
