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
    #STOP = "stopmac"
    print('STOP')
    s.sendto('slow00', (ip, port))
    s.sendto('fast00', (ip, port))
    s.sendto('slowds', (ip, port))
    s.sendto('fastds', (ip, port))

def startmach():
    #START = "startm"
    print('START')
    s.sendto('slowen', (ip, port))
    s.sendto('fasten', (ip, port))
    s.sendto('slow30', (ip, port))
    s.sendto('fast30', (ip, port))

def set_bin(new_bin):
    BIN = "sort"
    if new_bin >= 10:
        s.sendto(BIN + str(new_bin), (ip,port))
    elif new_bin == 0:
        s.sendto(BIN + "00", "utf-8", (ip,port))
    else:
        s.sendto(BIN + "0" + str(new_bin), (ip,port))
