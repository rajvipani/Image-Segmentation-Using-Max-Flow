from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import ImageTk
from PIL import Image
from tkinter import messagebox

from ctypes import cdll
from tkinter import ttk 
from ctypes import *
import cv2

if __name__ == "__main__":
    lib = cdll.LoadLibrary('./main.so')
    libedk = cdll.LoadLibrary('./../src/edk.so')
    libpushr = cdll.LoadLibrary('./../src/pushr.so')
    #lib.file_read_c.restype = POINTER(c_char_p * 256)
    #lib.file_read_c.argtypes = (c_char_p,c_char_p)
    lib.kmeans_clustering_c.argtypes = (c_char_p,c_char_p,c_char_p,c_char_p)
    libedk.edmondk_c.argtypes = (c_char_p,c_char_p,c_char_p,c_char_p)
    libpushr.pushr_c.argtypes = (c_char_p,c_char_p,c_char_p,c_char_p)
    #out = lib.test_funcc()


    root = Tk()
    root.title("EC504 - Project Demostration")

    image_scale = 250
    image_size = 50

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
    File = askopenfilename(parent=root, initialdir="../images/",title='Choose an image.',filetypes = (("image files","*.jpg"), ("all files", "*.*") ,("image files","*.png")) ) 
    img = ImageTk.PhotoImage(Image.open(File))
    if (img.width()>=50 and img.height()>=50):
        print("INFO: Rescaling image to 50x50")
        img = cv2.imread(File, cv2.IMREAD_GRAYSCALE)
        img = cv2.resize(img, (50,50), interpolation = cv2.INTER_AREA) 
        new_file = "resized.jpg"
        cv2.imwrite(new_file, img)  
        img = ImageTk.PhotoImage(Image.open(new_file).resize((image_scale,image_scale)))
        File = new_file
    else:
        img = ImageTk.PhotoImage(Image.open(File).resize((image_scale,image_scale)))
    print(File)
    canvas.create_image(0,0,image=img,anchor="nw")
    canvas.config(scrollregion=canvas.bbox(ALL))

    backg = []
    foreg = []
    num_of_pixels_from_each = 1
    ovals = []
    n = 0
    #function to be called when mouse is clicked
    def printcoords(event):
        #outputting x and y coords to console
        python_green = "#00FF00"
        python_red = "#FF0000"
        pixel_size = 4
        if (event.x>img.width() or event.y>img.height()):
            errorCallBack()
        else:
            x1, y1 = (event.x - pixel_size), (event.y - pixel_size)
            x2, y2 = (event.x + pixel_size), (event.y + pixel_size)
            global n, backg, foreg, ovals
            n = n + 1
            print (event.x*image_size/image_scale,event.y*image_size/image_scale)
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

    messagebox.showinfo( "Instructions", "Please select one background point and one foreground point on the image respectively.\nThese points will be used as seeds for max flow algorithms\nUse RESET button to reset the selection")

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
        outfile = create_string_buffer(256)
        outfile.value = b'dummy_word'

        #print(repr(outfile.value()))
        p.value = b'image_data.txt'
        out = lib.file_read_c(p,outfile)
        print(out)
        #print(repr(outfile.value()))
        #print(sizeof(outfile), repr(outfile.raw))
        print(outfile.value.decode("utf-8"))
        new_image_name = outfile.value.decode("utf-8")
        nwin = Toplevel()
        nwin.title("New Window")
        photo2 = PhotoImage(file = new_image_name)
        lbl2 = Label(nwin, image = photo2)
        lbl2.pack()
        nwin.mainloop()


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
                str1 = str(int(backg[i][0]*image_size/image_scale))+", "+str(int(backg[i][1]*image_size/image_scale))
                f.write(str1)
                f.write('\n')
            for i in range(0,len(foreg)):
                str2 = str(int(foreg[i][0]*image_size/image_scale))+", "+str(int(foreg[i][1]*image_size/image_scale))
                f.write(str2)
                f.write('\n')
            f.close()

    def points_check():
        global backg, foreg, num_of_pixels_from_each
        if (len(backg)!=num_of_pixels_from_each or len(foreg)!=num_of_pixels_from_each):
            messagebox.showerror( "ERROR", "ERROR: Required number of points are not selected, please reset and select again")

    def kmeans():
        points_check()
        global info_file
        p = create_string_buffer(20) # create 128 byte buffer
        outfile = create_string_buffer(256)
        time_o = create_string_buffer(128)
        iterl = create_string_buffer(128)
        outfile.value = b'dummy_word'
        p.value = b'image_data.txt'
        out = lib.kmeans_clustering_c(p,outfile,time_o,iterl)
        new_image_name = outfile.value.decode("utf-8")
        time_1 = time_o.value.decode("utf-8")
        iterl = iterl.value.decode("utf-8")
        nwin = Toplevel()
        nwin.title("K-Means image segmentation")
        photo2 = ImageTk.PhotoImage(Image.open(new_image_name).resize((image_scale,image_scale))) #file = new_image_name)
        lbl2 = Label(nwin, image = photo2)
        lbl2.pack()
        time_display = StringVar()
        time_display.set("Elapsed Time    : "+str(time_1)+" Seconds")
        iter_d = StringVar()
        iter_d.set("Iteration Count : "+str(iterl)) 
        lbl1 = Label(nwin, textvariable=time_display)
        lbl1.pack()
        lbl3 = Label(nwin, textvariable=iter_d)
        lbl3.pack()
        nwin.mainloop()

    def edk():
        points_check()
        global info_file
        p = create_string_buffer(20) # create 128 byte buffer
        outfile = create_string_buffer(256)
        time_o = create_string_buffer(128)
        iterl = create_string_buffer(128)
        outfile.value = b'dummy_word'
        p.value = b'image_data.txt'
        out = libedk.edmondk_c(p,outfile,time_o,iterl)
        new_image_name = outfile.value.decode("utf-8")
        time_1 = time_o.value.decode("utf-8")
        iterl = iterl.value.decode("utf-8")
        print(new_image_name)
        nwin = Toplevel()
        nwin.title("Edmond - Karp's Max-Flow Image Segmentation")
        photo2 = ImageTk.PhotoImage(Image.open(new_image_name).resize((image_scale,image_scale))) #file = new_image_name)
        lbl2 = Label(nwin, image = photo2)
        lbl2.pack()
        time_display = StringVar()
        time_display.set("Elapsed Time    : "+str(time_1)+" Seconds")
        iter_d = StringVar()
        iter_d.set("Iteration Count : "+str(iterl)) 
        lbl1 = Label(nwin, textvariable=time_display)
        lbl1.pack()
        lbl3 = Label(nwin, textvariable=iter_d)
        lbl3.pack()
        nwin.mainloop()


    def pushr():
        points_check()
        global info_file
        p = create_string_buffer(20) # create 128 byte buffer
        outfile = create_string_buffer(256)
        time_o = create_string_buffer(128)
        iterl = create_string_buffer(128)
        outfile.value = b'dummy_word'
        p.value = b'image_data.txt'
        out = libpushr.pushr_c(p,outfile,time_o,iterl)
        new_image_name = outfile.value.decode("utf-8")
        time_1 = time_o.value.decode("utf-8")
        iterl = iterl.value.decode("utf-8")
        nwin = Toplevel()
        nwin.title("Push - Relabel Max-Flow Image Segmentation")
        photo2 = ImageTk.PhotoImage(Image.open(new_image_name).resize((image_scale,image_scale))) #file = new_image_name)
        lbl2 = Label(nwin, image = photo2)
        lbl2.pack()
        time_display = StringVar()
        time_display.set("Elapsed Time    : "+str(time_1)+" Seconds")
        iter_d = StringVar()
        iter_d.set("Iteration Count : "+str(iterl)) 
        lbl1 = Label(nwin, textvariable=time_display)
        lbl1.pack()
        lbl3 = Label(nwin, textvariable=iter_d)
        lbl3.pack()
        nwin.mainloop()


    OPTIONS = [1,2,3,4,5]
    variable = StringVar(root)


    B = Button(root, text ="Reset Selection", command = reset_sel)
    B.pack(side=LEFT)

    B2 = Button(root, text ="Store Coordinates", command = store_coords)
    B2.pack(side=LEFT)

    # B4 = Button(root, text ="Call CPP", command = cpp)
    # B4.pack()

    B4 = Button(root, text ="K-Means", command = kmeans)
    B4.pack(side=LEFT)

    B5 = Button(root, text ="EdmondKarp", command = edk)
    B5.pack(side=LEFT)

    B6 = Button(root, text ="Push-Relabel", command = pushr)
    B6.pack(side=LEFT)

    B3 = Button(root, text ="Exit", command = exit)
    B3.pack(side=RIGHT)

    root.mainloop()