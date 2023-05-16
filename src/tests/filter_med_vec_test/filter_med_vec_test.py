import pyccante as py

img = py.Image("crash.bmp", py.LDR_type.LT_NONE)

imgOut = py.FilterMedVec.execute(img, 1)

imgOut.Write("filtered.png")