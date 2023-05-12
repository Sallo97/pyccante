import pyccante as py

# Creating image objects
imgIn = py.Image("./finalbout.png",py.LDR_type.LT_NOR)
imgOut = py.Image()

# Create and apply filter
imgOut = py.FilterGaussian2D.execute(imgIn, imgOut, 16.12)
 
# Write filtered image
imgOut.Write("./filtered.png")
