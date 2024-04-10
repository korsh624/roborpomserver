import socket
import time

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
serverAddressPort = ("192.168.42.15", 8888)


def setConveer(speed):
    UDPClientSocket.sendto(str.encode("r#"), serverAddressPort)
    UDPClientSocket.sendto(str.encode(f"s:{speed}#"), serverAddressPort)
#
# setConveer(150)
# time.sleep(20)
setConveer(0)
time.sleep(2)
