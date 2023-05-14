import pyccante as py

imgIn = py.Image("img.png", py.LDR_type.LT_NOR)

conv = py.Image("conv.png", py.LDR_type.LT_NOR)

imgOut = py.Image()

imgOut = py.FilterConv2D.execute(&imgIn, &conv, &imgOut)

imgOut.Write("filtered.png")