import pyccante as py

img = py.Image("scrtgnt.png", py.LDR_type.LT_NONE)

imgOut = py.FilterMax.execute(img, 1)

imgOut.Write("filtered.png")