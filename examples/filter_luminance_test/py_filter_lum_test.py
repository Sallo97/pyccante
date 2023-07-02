import pyccante as py

# Creating image objects
imgIn_1 = py.Image("./img1.png",py.LDR_type.LT_NOR)
imgIn_2 = py.Image("./img2.png", py.LDR_type.LT_NOR)
imgOut_1 = py.Image()
imgOut_2 = py.Image()

# Create and apply filter ti imgIN_2
filter = py.FilterLuminance()
imgOut_1 = filter.execute(imgIn_1, imgOut_1)
imgOut_2 = py.FilterLuminance.execute(imgIn_2, imgOut_2, py.LUMINANCE_TYPE.LT_CIE_LUMINANCE)
 
# Write filtered images
imgOut_1.Write("./luminance1.png")
imgOut_2.Write("./luminance2.png")