import socket
import time

ip = '127.0.0.1'
port = 5008
#START = "startm"
#STOP = "stopmac"

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect((ip, port))

def stopmach():
    #START = "startm"
    STOP = "stopmac"
    print(STOP)
    s.sendto(bytes(STOP, "utf-8"), (ip, port))

def startmach():
    START = "startm"
    print(START)
    s.sendto(bytes(START, "utf-8"), (ip,port))

def set_bin(new_bin):
    BIN = "sort"
    if new_bin >= 10:
        s.sendto(bytes(BIN + str(new_bin), "utf-8"), (ip,port))
    elif new_bin == 0:
        s.sendto(bytes(BIN + "00", "utf-8"), (ip,port))
    else:
        s.sendto(bytes(BIN + "0" + str(new_bin), "utf-8"), (ip,port))
