# This program test the computePoissonImageEditing of pyccante


import pyccante as pyc
import numpy as np

    
img0_str = "../_data/input/poisson/target.png"
img1_str = "../_data/input/poisson/source.png"
img2_str = "../_data/input/poisson/mask.png"

print("Reading images...")

    
img_target = pyc.Image(img0_str,pyc.LT_NOR)
img_source = pyc.Image(img1_str, pyc.LT_NOR)
mask_source = pyc.Image(img2_str, pyc.LT_NOR)

print("Ok\n")

print("Are images valid? ")
if img_target.isValid() and img_source.isValid() and mask_source.isValid():
    print("OK\n")

    color =  np.array([1.0, 1.0, 1.0], np.float32)
    mask = mask_source.convertToMask(color, 0.1, False)

    imgOut = pyc.computePoissonImageEditing(img_source, img_target, mask)

    imgOut.Write("../_data/output/poisson_blending_result.png", pyc.LT_NOR)
else:
    print("Images are not valid!\n")
