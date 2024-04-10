import socket
import time

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
serverAddressPort = ("192.168.42.12", 8888)


def moveManipulator(x, y, z, a, g):
    UDPClientSocket.sendto(str.encode("r#"), serverAddressPort)
    UDPClientSocket.sendto(str.encode(f"g:{x}:{y}:{a}:{z}:{g}#"), serverAddressPort)

def iteration():
    moveManipulator(150, 80, 140, 0, 0)
    time.sleep(2)
    moveManipulator(163, -140, 140, 0, 0)
    time.sleep(2)
    moveManipulator(163, -140, -10, 0, 0)
    time.sleep(0.1)
    moveManipulator(163, -140, -10, 0, 1)
    time.sleep(2)
    moveManipulator(163, -140, 140, 0, 1)
    time.sleep(2)
    moveManipulator(160, 80, 5, 0, 1)
    time.sleep(0.1)
    moveManipulator(160, 80, 5, 0, 0)
    time.sleep(2)
    moveManipulator(150, 80, 140, 0, 0)