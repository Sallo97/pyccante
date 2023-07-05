import pyccante as py
import numpy as np

img = py.Image()

img.Read("../_data/connected_test.png", py.LDR_type.LT_NOR)

cc = py.ConnectedComponents()

color = np.array( [ 0.0, 0.0, 0.0], np.float32)
mask = img.convertToMask( color, 0, True )

img_cc = cc.execute(mask, img.width, img.height)

areaMin = img.nPixels()

for i in img_cc[1]:
    areaTmp = len( i.coords )
    if (areaMin > areaTmp):
        areaMin = areaTmp
        
print(f"The size of the smallest cicle is :{areaMin} pixels.")

comp = py.ConnectedComponents.convertFromIntegerToImage(img_cc[0], img.width, img.height)
comp.Write("connected_components.pfm")