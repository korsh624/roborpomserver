import socket
import time

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
serverAddressPort = ("192.168.42.14", 8888)

r = False
n = 0
while True:
    r = not r
    n += 1
    msgFromClient = "r:"+str(int(r))+":1:0:0:2:Hello"+str(n)+"#"
    print(msgFromClient)
    bytesToSend = str.encode(msgFromClient)
    bufferSize = 1024
    UDPClientSocket.sendto(bytesToSend, serverAddressPort)
    time.sleep(1)
