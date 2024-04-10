import serial
from time import sleep

ser = serial.Serial('COM9', 9600, timeout=2)
sleep(2)

def com():
    message = ser.readline()
    message = message.strip()
    result = message.decode()
    return result

while True:
   com()







