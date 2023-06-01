import pyccante as pyc

img = pyc.Image("./test.hdr", pyc.LDR_type.LT_NONE)
array = img.getMaxVal()
print(array)