import pyccante as py

img = py.Image()
img.Read("bottles.hdr")

imgOut = py.ReinhardTMO.executeGlobal1(img)
imgOut.Write("reinhard_gtmo1.png")

imgOut = py.ReinhardTMO.executeGlobal2(img)
imgOut.Write("reinhard_gtmo2.png")

imgOut = py.ReinhardTMO.executeLocal1(img)
imgOut.Write("reinhard_ltmo1.png")

imgOut = py.ReinhardTMO.executeLocal2(img)
imgOut.Write("reinhard_ltmo2.png")