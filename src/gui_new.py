from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import ImageTk
from PIL import Image
from tkinter import messagebox

from ctypes import cdll
from tkinter import ttk 
from ctypes import *

if __name__ == "__main__":
    lib = cdll.LoadLibrary('./main.so')
    lib.file_read_c.argtypes = c_char_p,

    out = lib.test_funcc()


    root = Tk()

    #setting up a tkinter canvas with scrollbars
    frame = Frame(root, bd=2, relief=SUNKEN)
    frame.grid_rowconfigure(0, weight=1)
    frame.grid_columnconfigure(0, weight=1)
    xscroll = Scrollbar(frame, orient=HORIZONTAL)
    xscroll.grid(row=1, column=0, sticky=E+W)
    yscroll = Scrollbar(frame)
    yscroll.grid(row=0, column=1, sticky=N+S)
    canvas = Canvas(frame, bd=0, xscrollcommand=xscroll.set, yscrollcommand=yscroll.set)
    canvas.grid(row=0, column=0, sticky=N+S+E+W)
    xscroll.config(command=canvas.xview)
    yscroll.config(command=canvas.yview)
    frame.pack(fill=BOTH,expand=1)

    #adding the image
    File = askopenfilename(parent=root, initialdir="./",title='Choose an image.',filetypes = (("image files","*.jpg"), ("all files", "*.*") ,("image files","*.png")) ) 
    img = ImageTk.PhotoImage(Image.open(File))
    print(File)
    canvas.create_image(0,0,image=img,anchor="nw")
    canvas.config(scrollregion=canvas.bbox(ALL))

    backg = []
    foreg = []
    num_of_pixels_from_each = 2
    ovals = []
    n = 0
    #function to be called when mouse is clicked
    def printcoords(event):
        #outputting x and y coords to console
        python_green = "#476042"
        python_red = "#FF0000"
        pixel_size = 4
        if (event.x>img.width() or event.y>img.height()):
            errorCallBack()
        else:
            x1, y1 = (event.x - pixel_size), (event.y - pixel_size)
            x2, y2 = (event.x + pixel_size), (event.y + pixel_size)
            global n, backg, foreg, ovals
            n = n + 1
            print (event.x,event.y)
            if (n <= num_of_pixels_from_each):
                backg.append((event.x,event.y))
                ovals.append( canvas.create_oval(x1, y1, x2, y2, fill=python_green) )
            elif (n <= num_of_pixels_from_each*2):
                foreg.append((event.x,event.y))
                ovals.append( canvas.create_oval(x1, y1, x2, y2, fill=python_red) )
            else:
                messagebox.showinfo( "You are done!", "You have already selected the required number of points, store selection and proceed!")

    #mouseclick event
    canvas.bind("<Button 1>",printcoords)

    messagebox.showinfo( "Instructions", "Please select two background points and two foreground points on the image respectively.\nThese points will be used as seeds for max flow algorithms\nUse RESET button to reset the selection")

    info_file = "image_data.txt"

    def reset_sel():
        global n, backg, foreg, ovals
        for i in range(0,len(ovals)):
            canvas.delete(ovals[i])
        ovals = []
        foreg = []
        backg = []
        n = 0
        messagebox.showinfo( "Reset", "Selection cleared, please select the points again.")


    def cpp():
        global info_file
        p = create_string_buffer(20) # create 128 byte buffer
        p.value = b'image_data.txt'
        out = lib.file_read_c(p)
        print(out)


    def errorCallBack():
        messagebox.showerror( "ERROR", "ERROR: Please select points inside the image")

    def store_coords():
        global backg, foreg, File
        if (len(backg)!=num_of_pixels_from_each or len(foreg)!=num_of_pixels_from_each):
            messagebox.showerror( "ERROR", "ERROR: Required number of points are not selected, please reset and select again")
        else:
            f = open(info_file, "w")
            f.write(File)
            f.write('\n')
            f.write(str(num_of_pixels_from_each))
            f.write('\n')
            for i in range(0,len(backg)):
                str1 = str(backg[i][0])+", "+str(backg[i][1])
                f.write(str1)
                f.write('\n')
            for i in range(0,len(foreg)):
                str2 = str(foreg[i][0])+", "+str(foreg[i][1])
                f.write(str2)
                f.write('\n')
            f.close()


    OPTIONS = [1,2,3,4,5]
    variable = StringVar(root)
    #variable.set(OPTIONS[0]) # default value
    
    def display_selected_item_index(event): 
       global so, num_of_pixels_from_each
       #print ('index of this item is: {}\n'.format(so.current()))
       num_of_pixels_from_each =  OPTIONS[so.current()]
       print(num_of_pixels_from_each)
    
    def OptionCallBack(*args):
        print (variable.get())
    
    #variable = StringVar(app)
    variable.set("Select number of points")
    variable.trace('w', OptionCallBack)
    
    so = ttk.Combobox(root, textvariable=variable)
    so.config(values =(1,2,3,4,5))
    #so.grid(row=1, column=4, sticky='E', padx=10)    
    so.bind("<<ComboboxSelected>>", display_selected_item_index) 
    so.pack()


    B = Button(root, text ="Reset Selection", command = reset_sel)
    B.pack()

    B2 = Button(root, text ="Store Coordinates", command = store_coords)
    B2.pack()

    B3 = Button(root, text ="Exit", command = exit)
    B3.pack()

    B4 = Button(root, text ="Call CPP", command = cpp)
    B4.pack()
    # var = StringVar()
    # label = Message( root, textvariable=var, relief=RAISED )

    # var.set("Select two background points")
    # label.pack()

    root.mainloop()