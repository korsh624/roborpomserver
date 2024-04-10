# -*- coding: utf-8 -*-
import robot
import serial
import time


r = robot.Robot()
r.connect('COM6', None) #подключение к dinamixel

ser = serial.Serial('COM4', 9600) #подключение к ардуино
time.sleep(1)

while True:
    try:
        print(" ")
        message_com = ser.readline()
        print(message_com)

        message_com = message_com.strip()
        message_com = message_com.decode()
        print(message_com)

        motor = message_com[0:2]
        print("motor", motor)
        angle = message_com[2:6]
        print("angle", angle)

        r.setJoint(motor, int(angle / 10))
        time.sleep(5)
    except:
        print("error")
