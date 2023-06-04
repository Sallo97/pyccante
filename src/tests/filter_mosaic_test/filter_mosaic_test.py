import pyccante as py

imgIn = py.Image("image.png", py.LDR_type.LT_NONE)


imgOut = py.FilterMosaic.execute(imgIn)

imgOut.Write("filtered.png")