import pyccante as py

imgIn = py.Image("rabbit.png", py.LDR_type.LT_NOR)

imgOut = py.Image()

imgOut = py.FilterMosaic.execute(imgIn, imgOut)

imgOut.Write("filtered.png")