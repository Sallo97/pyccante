import pyccante as py

imgIn = py.Image("pacman.png", py.LDR_type.LT_NOR)
imgOut = py.Image()
imgOut = py.FilterBilateral2DF.execute(imgIn, imgOut, 1.5, 100.6)
imgOut.Write("filtered.png")