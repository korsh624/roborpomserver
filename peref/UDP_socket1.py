# Use UDP_socket to control things without of using GUI
# You may add more things and command to control equipment

import socket
import time

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


# If you want to use more things, add others using example:

# angle_manipulator = ("192.168.1.153", 8888) # angle_manipulator - NAME; 192.168.1.153 - IP of thing; 8888 - port. Change IP!
# traffic_light = ("192.168.137.111", 8888)
palletizer_manipulator = ("192.168.42.241", 8888)
angle_manipulator=('192.168.42.12',8888)
core=('192.168.42.17',8888)

while True:
# UDP command:


    udp_socket.sendto(b'c:200:10:15#', core)


# udp_socket.sendto(b'p:200:0:0:1#', palletizer_manipulator)# 'p:200:0:0:0#' - 'p : coord. X : coord. Y : 0/1 - down/up gripper : 0/1 - switch off/on pump#'
# 'g' - angle manipulator / 'p' - palletizer manipulator; 
#udp_socket.sendto(b'g:200:0:0:0:0#', angle_manipulator) # 'g:200:0:0:0:0#' - 'g : coord. X : coord. Y : coord. T : 0/1 - down/up gripper : 0/1 - switch off/on pump#'


time.sleep(2)# Pause 3 sec.


# Add more command...