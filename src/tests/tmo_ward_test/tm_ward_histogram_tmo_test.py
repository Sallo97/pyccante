import pyccante as py

img = py.Image()
img.Read("bottles.hdr")

imgOut = py.WardHistogramTMO.execute(img)
imgOut.Write("ward_tmo.png")