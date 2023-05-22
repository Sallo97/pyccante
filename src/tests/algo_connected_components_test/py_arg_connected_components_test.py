import pyccante as py
import numpy as np

img = py.Image()

img.Read("connected_test.png", py.LDR_type.LT_NOR)

cc = py.ConnectedComponents()

color = np.array( [ 0.0, 0.0, 0.0], np.float32)
mask = img.convertToMask( color, 0, True)



img_cc = cc.execute(mask, img.width, img.height)

print(img_cc.ret)
print(img_cc.imgOut)

areaMin = img.nPixels()

#for i in range(ret.size()):
#    areaTmp = ret[i].coords.size()
#    if areaMin > areaTmp:
#        areaMin = areaTmp
        
#print(f"The size of the smallest cicle in :{areaMin} pixels.")

#comp = py.ConnectedComponents.convertFromIntegerToImage(img_cc.imgOut, img.width, img.height)
#comp.Write("connected_components.pfm")