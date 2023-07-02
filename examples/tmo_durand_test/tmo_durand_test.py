import pyccante as py

img = py.Image()
img.Read("bottles.hdr")

imgOut = py.DurandTMO.execute(img)
imgOut.Write("durand_tmo.png")