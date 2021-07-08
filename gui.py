## Toggle an LED when the GUI button is pressed ##

from Tkinter import *
#import Tkinter.font
from gpiozero import LED
import RPi.GPIO   # for Python2
RPi.GPIO.setmode(RPi.GPIO.BCM)

### HARDWARE DEFINITIONS ###
led=LED(14)

### GUI DEFINITIONS ###
win = Tk()
win.title("LED Toggler")
myFont = tkinter.font.Font(family = 'Helvetica', size = 12, weight = "bold")


### Event Functions ###
def ledToggle():
    if led.is_lit:
        led.off()
        ledButton["text"]="Turn LED on" # Change only the button text property
    else:
        led.on()
        ledButton["text"]="Turn LED off"

def close():
    RPi.GPIO.cleanup()
    win.destroy()



### WIDGETS ###

# Button, triggers the connected command when it is pressed
ledButton = Button(win, text='Turn LED on', font=myFont, command=ledToggle, bg='bisque2', height=1, width=24)
ledButton.grid(row=0,column=1)

exitButton = Button(win, text='Exit', font=myFont, command=close, bg='red', height=1, width=6)
exitButton.grid(row=2, column=1)

win.protocol("WM_DELETE_WINDOW", close) # cleanup GPIO when user closes window

win.mainloop() # Loops forever

