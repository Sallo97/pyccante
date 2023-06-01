import pyccante as py

img = py.Image("crash.bmp", py.LDR_type.LT_NONE)

imgOut = py.FilterBilateral2DS.execute(img, 2.5, 2.5)

imgOut.Write("filtered.png", py.LDR_type.LT_NONE)