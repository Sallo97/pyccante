import pyccante as py

img = py.Image()
img.Read("bottles.hdr")

imgOut = py.ExposureFusion.execute(img)
imgOut.Write("exposure_fusion.png")