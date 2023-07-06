# This program test the FilterBilatera2DF and FilterBilateral2DS of pyccante


import pyccante as pyc

img_str = "../_data/input/tommaseo_statue.png"

print("Reading an image...")
img = pyc.Image(img_str)

print("Ok\n")

if img.isValid():
    
    out_1 = pyc.FilterBilateral2DF.execute(img, 4.0, 0.05)
    out_2 = pyc.FilterBilateral2DS.execute(img, 4.0, 0.05)
    out_1.Write("../_data/output/filter_bilateral_2df.png")
    out_2.Write("../_data/output/filter_bilateral_2ds.png")

    print("Ok\n")

else:
    print("The image is not valid!")
    