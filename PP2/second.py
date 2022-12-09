# import library
import tkinter as tk
from tkinter import ttk

#avec get() on peut avoir le string et en comptant les points 
#on aura le nombre de phrases et en comptant les espaces
#on aura le nombre de mots

def count():
    rsel = rvar.get()
    if rsel == 1: 
        var = 0
        for i in inp.get():
            if i== '.':
                var = var+1
        lab2.config(text=str(var)) 
    elif rsel == 2: 
        var = 1
        for i in inp.get():
            if i== ' ':
                var = var+1
        lab2.config(text=str(var))       
    elif rsel == 3: 
        lab2.config(text=str(len(inp.get())))

# create a window, inside you can add button, text...
win = tk.Tk()
win.title("String Count")
win.resizable(False, False)
rvar = tk.IntVar()

# write text, choose location
lab1 = ttk.Label(win, text="Input String")
lab1.grid(column=0, row=0)

# enter a zone to write a string
inp = tk.StringVar( )
in_line = ttk.Entry(win, width=30, textvariable = inp)
in_line.grid(column=0, row=1)


lab2 = ttk.Label(win, text="")
lab2.grid(column=0, row=3)
#lab2.config(text=inp)


# create button and connect it to function count
rb1 = tk.Radiobutton(win, text ="sentence", variable =rvar, value =1, command =count)
rb1.grid(column=1, row=0, columnspan=3, sticky= tk.W)

rb2 = tk.Radiobutton(win, text ="word", variable =rvar, value =2, command =count)
rb2.grid(column=1, row=1, columnspan=3)

rb3 = tk.Radiobutton(win, text ="character", variable =rvar, value =3, command =count)
rb3.grid(column=1, row=2, columnspan=3)



win.mainloop()



