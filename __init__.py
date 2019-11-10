#!/usr/bin/python
from Tkinter import *
 
# Main window 
mainwindow = Tk()
mainwindow.title("RF Signal Generator")
mainwindow.geometry('600x400')


#  Handlers - need to be declared before widget is defined
def clickedMute1():

    lbl.configure(text="Button was clicked !!") 
  
def clickedMute2():

    lbl.configure(text="Button was clicked !!") 

def clickedMute3():

    lbl.configure(text="Button was clicked !!") 

def clickedUpdate():
   var = mainwindow.focus_get().get()
   lbl.configure(text = var)


def keypad1():
    #Insert digit at end of variable in window in focus
    mainwindow.focus_get().insert(END,"1") 
    
def keypad2():

    mainwindow.focus_get().insert(END,"2") 

def keypad3():

    mainwindow.focus_get().insert(END, "3") 
    
def keypad4():

    mainwindow.focus_get().insert(END, "4") 

def keypad5():

    mainwindow.focus_get().insert(END, "5") 

def keypad6():

    mainwindow.focus_get().insert(END, "6") 

def keypad7():

    mainwindow.focus_get().insert(END, "7") 

def keypad8():

    mainwindow.focus_get().insert(END, "8") 

def keypad9():

    mainwindow.focus_get().insert(END, "9") 

def keypad0():

    mainwindow.focus_get().insert(END, "0") 

def keypadminus():

    mainwindow.focus_get().insert(END, "-") 
    
def keypaddot():

    mainwindow.focus_get().insert(END, ".") 
     
   
#Widgets 
# First row labels
lbl = Label(mainwindow, text="Generator 1")
lbl.grid(column=2, row=0)
lbl = Label(mainwindow, text="Generator 2")
lbl.grid(column=4, row=0)
lbl = Label(mainwindow, text="Generator 3")
lbl.grid(column=6, row=0)

# Second row 
# Frequency indicators
lbl = Label(mainwindow, text="Frequency")
lbl.grid(column=0, row=1)

freqGen1 = Entry(mainwindow,width=10)
freqGen1.grid(column=2, row=1)
lbl = Label(mainwindow, text="MHz")
lbl.grid(column=3, row=1)

# Set up variable associated with this entry



freqGen2 = Entry(mainwindow,width=10)
freqGen2.grid(column=4, row=1)
lbl = Label(mainwindow, text="MHz")
lbl.grid(column=5, row=1)

freqGen3 = Entry(mainwindow,width=10)
freqGen3.grid(column=6, row=1)
lbl = Label(mainwindow, text="MHz")
lbl.grid(column=7, row=1)

# Third Row space 

#Fourth Row - levels 
lbl = Label(mainwindow, text="Level")
lbl.grid(column=0, row=3)

levelGen1 = Entry(mainwindow,width=10)
levelGen1.grid(column=2, row=3)
lbl = Label(mainwindow, text="dBm")
lbl.grid(column=3, row=3)

levelGen2 = Entry(mainwindow,width=10)
levelGen2.grid(column=4, row=3)
lbl = Label(mainwindow, text="dBm")
lbl.grid(column=5, row=3)

levelGen3 = Entry(mainwindow,width=10)
levelGen3.grid(column=6, row=3)
lbl = Label(mainwindow, text="dBm")
lbl.grid(column=7, row=3) 

# Fifth row space

# Sixth Row Mute 
lbl = Label(mainwindow, text="")
lbl.grid(column=0, row=6)

mute1 = Button(mainwindow, text="Mute", command=clickedMute1)
mute1.grid(column=2, row=6)
lbl = Label(mainwindow, text="")
lbl.grid(column=3, row=5)

mute2 = Button(mainwindow, text="Mute", command=clickedMute2)
mute2.grid(column=4, row=6)
lbl = Label(mainwindow, text="")
lbl.grid(column=5,  row=5)

mute3 = Button(mainwindow, text="Mute", command=clickedMute3)
mute3.grid(column=6, row=6)
lbl = Label(mainwindow, text="")
lbl.grid(column=7, row=5)

# Keys to enter data 
# Inside a frame called keypad
keypad = Frame(mainwindow,  bg  = "yellow",  borderwidth = 3)
keypad.grid(column = 12,  row = 2)

btn = Button(keypad, text=" 1 ",   command=keypad1)
btn.grid(column=0, row=0)

btn = Button(keypad, text=" 2 ",   command=keypad2)
btn.grid(column=1, row=0)

btn = Button(keypad, text=" 3 ",   command=keypad3)
btn.grid(column=2, row=0)

btn = Button(keypad, text=" 4 ",   command=keypad4)
btn.grid(column=0, row=1)

btn = Button(keypad, text=" 5 ",   command=keypad5)
btn.grid(column=1, row=1)

btn = Button(keypad, text=" 6 ",   command=keypad6)
btn.grid(column=2, row=1)

btn = Button(keypad, text=" 7 ",   command=keypad7)
btn.grid(column=0, row=2)

btn = Button(keypad, text=" 8 ",   command=keypad8)
btn.grid(column=1, row=2)

btn = Button(keypad, text=" 9 ",   command=keypad9)
btn.grid(column=2, row=2)

btn = Button(keypad, text=" - ",   command=keypadminus)
btn.grid(column=0, row=3)

btn = Button(keypad, text=" 0 ",   command=keypad0)
btn.grid(column=1, row=3)

btn = Button(keypad, text=" . ",   command=keypaddot)
btn.grid(column=2, row=3)

btn = Button(mainwindow, text="Update Generator", command=clickedUpdate)
btn.grid(column=12, row=6)

# Set focus to freqGen1 to start
freqGen1.focus()

mainwindow.mainloop()

