import pyccante as py
import numpy as np

imgIn_1 = py.Image("yosh.png", py.LDR_type.LT_NOR)
imgIn_2 = py.Image("rabbit.png", py.LDR_type.LT_NOR)

imgOut_1 = py.Image()
imgOut_2 = py.Image()

mtx = np.matrix('1 2 3; 4 5 6; 7 8 9')

imgOut_1 = py.FilterRotation.execute(imgIn_1, imgOut_1, 10, 25.5, 10.9)
imgOut_2 = py.FilterRotation.execute(imgIn_2, imgOut_2, mtx)

imgOut_1.Write("filtered1.png")
imgOut_2.Write("filtered2.png")