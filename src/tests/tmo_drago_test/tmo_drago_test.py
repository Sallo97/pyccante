import pyccante as py

img = py.Image()
img.Read("bottles.hdr")

imgOut = py.DragoTMO.execute(img)
imgOut.Write("drago_tmo.png")