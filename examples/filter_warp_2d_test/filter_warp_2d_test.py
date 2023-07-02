import numpy as np
import pyccante as py

img = py.Image("Wart.jpg", py.LDR_type.LT_NONE)
imgOut = py.Image()

a = np.array( [1, 0, 0, 2, 1, 0, 2, 3, 1], np.float32)
mtx = py.Matrix3x3(a)
mtx.print()

imgOut = py.FilterWarp2D.execute(img, imgOut, mtx, True, False)