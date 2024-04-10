import socket
import time

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
serverAddressPort = ("192.168.42.15", 8888)

states = [
    "l:1:0:0:0#",
    "l:0:0:0:1#",
    "l:0:0:1:0#",
    "l:0:1:0:0#"
]


counter = 0
cdir = 1
while True:

    msgFromClient = states[counter]
    print(msgFromClient)
    bytesToSend = str.encode(msgFromClient)
    bufferSize = 1024
    UDPClientSocket.sendto(bytesToSend, serverAddressPort)
    if cdir:
        counter += 1
    else:
        counter -= 1
    if counter >= 3 or counter <= 0:
        cdir = not cdir

    time.sleep(0.5)

