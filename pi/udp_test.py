#!/usr/bin/python3

import socket
import time

ip = '127.0.0.1'
port = 5008

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while(True):
    sock.sendto(bytes('WORKS!1', 'utf-8'), (ip, port))
    time.sleep(1)