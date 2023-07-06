# This program test the FilterWarp2D of Piccante


import pyccante as pyc
import numpy as np

img0_str = "../_data/input/balcony_0.png"
    
img0 = pyc.Image(img0_str, pyc.LT_NOR)
    
print("Ok\n")

print("Is it valid? ")
if img0.isValid():
    print("OK\n")

    mtx_data = np.array([1, 0, 1, 1, 1, 1, 0, 0, 1], np.float32)
    H = pyc.Matrix3x3(mtx_data)
    print("matrix...:")
    print(H)

    print("Applying H to the image..")
    img0_H = pyc.FilterWarp2D.execute(img0, H, True, False)
    img0_H.Write("../_data/output/filter_warp_2d.png", pyc.LDR_type.LT_NOR)
    print("Ok.\n")
else:
    print("No it is an invalid file!\n")
