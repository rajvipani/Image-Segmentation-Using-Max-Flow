from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import ImageTk
from PIL import Image
from tkinter import messagebox

from ctypes import cdll



if __name__ == "__main__":
    lib = cdll.LoadLibrary('./main.so')

    out = lib.test_funcc()

    root = Tk()

    #setting up a tkinter canvas with scrollbars
    frame = Frame(root, bd=2, relief=SUNKEN)
    frame.grid_rowconfigure(0, weight=1)
    frame.grid_columnconfigure(0, weight=1)
    #xscroll = Scrollbar(frame, orient=HORIZONTAL)
    #xscroll.grid(row=1, column=0, sticky=E+W)
    #yscroll = Scrollbar(frame)
    #yscroll.grid(row=0, column=1, sticky=N+S)
    canvas = Canvas(frame, bd=0)#, #xscrollcommand=xscroll.set, yscrollcommand=yscroll.set)
    canvas.grid(row=0, column=0, sticky=N+S+E+W)
    #xscroll.config(command=canvas.xview)
    #yscroll.config(command=canvas.yview)
    frame.pack(fill=BOTH,expand=1)

    #adding the image
    File = askopenfilename(parent=root, initialdir="./",title='Choose an image.',filetypes = (("image files","*.jpg"), ("all files", "*.*") ,("image files","*.png")) ) 
    img = ImageTk.PhotoImage(Image.open(File))
    canvas.create_image(0,0,image=img,anchor="nw")
    canvas.config(scrollregion=canvas.bbox(ALL))

    backg = []
    foreg = []
    #function to be called when mouse is clicked
    def printcoords(event):
        #outputting x and y coords to console
        python_green = "#476042"
        pixel_size = 2
        if (event.x>img.width() or event.y>img.height()):
            errorCallBack()
        else:
            x1, y1 = (event.x - pixel_size), (event.y - pixel_size)
            x2, y2 = (event.x + pixel_size), (event.y + pixel_size)
            canvas.create_oval(x1, y1, x2, y2, fill=python_green)
            print (event.x,event.y)
    #mouseclick event
    canvas.bind("<Button 1>",printcoords)

    messagebox.showinfo( "Instructions", "Please select two background points and two foreground points on the image respectively.\nThese points will be used as seeds for max flow algorithms\nUse RESET button to reset the selection")

    def helloCallBack():
        messagebox.showinfo( "Hello Python", "Hello World")

    def errorCallBack():
        messagebox.showerror( "ERROR", "ERROR: Please select only inside the image")


    B = Button(root, text ="Hello", command = helloCallBack)

    B.pack()

    var = StringVar()
    label = Message( root, textvariable=var, relief=RAISED )

    var.set("Select two background points")
    label.pack()

    root.mainloop()