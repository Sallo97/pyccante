# This program test the FilterGaussian2D of pyccante


import pyccante as pyc

name_str = "../_data/input/balcony_0.png"
    
print("Reading an HDR file...")

img = pyc.Image(name_str)

print("Ok\n")

print("Is it valid? ")
if img.isValid(): 
    print("Ok\n")

    print("Filtering the image with a Gaussian filter with sigma = 4.0...")
    output = pyc.FilterGaussian2D.execute(4.0)

    print("Ok!\n")

    print("Writing the file to disk...")
    output.Write("../_data/output/filter_gaussian_2d.png")
else:
    print("The image is not valid.")    
