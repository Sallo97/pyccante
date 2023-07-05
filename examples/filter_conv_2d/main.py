# This program test the FilterConv2D of pyccante

import pyccante as pyc

img_str = "../_data/input/yellow_flowers.png"
psf_str = "../_data/input/kernel_psf.png"

print("Reading images...")


img = pyc.Image(img_str)
psf = pyc.Image(psf_str)

print("Ok\n")

print("Is it valid? ")
if img.isValid() and psf.isValid():
    print("Ok\n")

    # Normalization of the PSF
    psf /= psf.getSumVal()[0]

    # Applying FilterConv2D 
    conv = pyc.FilterConv2D.execute(psf)
    conv.Write("../_data/output/filter_conv2d.png")
        
    print("Ok!\n")

else:
    print("No, the image is not valid!")