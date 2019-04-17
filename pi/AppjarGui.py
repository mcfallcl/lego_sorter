#!/usr/bin/python3

from appJar import *

from PIL import Image
import PIL.ImageTk
from tkinter import *
#UDPserver.py
from UDPserver import startmach
from UDPserver import stopmach
from UDPserver import set_bin

window = Tk()

window.title("Welcome To The Lego Sorter")

#Background Image
bg_image = PhotoImage(file = "/home/pi/Pictures/Lego.gif")

w = bg_image.width()
h = bg_image.height()

window.geometry("%dx%d+20+200" % (w,h))

c = Canvas(window, height = h, width = w)
c.pack(side = TOP, fill = "both", expand = True)

c.create_image(0, 0, image = bg_image, anchor = 'nw')

#code for buttons
start = Button(c, text = "START", bg = "#00ff00", bd = 4, font = ('Twiddlestix', 25), command = lambda: startmach())
#start.config(height = 3, width = 5)
start.pack(side = 'left', padx = 110, pady = 10)
stop = Button(c, text = "STOP", bg = "red", fg = "white", bd = 6, font = ('Twiddlestix', 27, 'bold'), command = lambda: stopmach())
#stop.config(height = 6, width = 13)
stop.pack(side = 'left', pady = 90)

cur_bin = 0
def move_to_bin():
    global cur_bin
    set_bin(cur_bin)
    cur_bin = cur_bin + 1
    if cur_bin > 13:
        cur_bin = 0
sort_button = Button(c, text = "SORT", command = lambda: move_to_bin())
sort_button.pack(side = 'left', pady=80)

log = Button(c, text = "LOG", bg = "#00bfff", fg = "yellow", bd = 5, font = ('Twiddlestix', 23))
#log.config(height = 3, width = 3)
log.pack(side = 'top', pady = 120)

window.attributes('-fullscreen', True)
window.bind('<Escape>', lambda e: window.destroy())
           
window.mainloop()

