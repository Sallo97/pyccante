#This program test the FilterMosaic of pyccante


import pyccante as pyc

img_str = "../_data/input/yellow_flowers.png"
    

img = pyc.Image(img_str)

print("Is it valid? ")
if img.isValid(): 

    print("OK\n")

    print("Applying FilterMosaic...\n")
    out = pyc.FilterMosaic.execute(img)
    print("Ok\n")

    out.Write("../_data/output/filter_mosaic.png")
    print("Ok\n")
else:
    print("No, the file is not valid!\n")
