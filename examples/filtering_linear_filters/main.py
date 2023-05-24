import pyccante as pyc

name_hdr = '../data/bottles.hdr'

print("Reading an HDR file")
img = py.Image()
img.Read(name_hdr)
print("Ok")

print("Is it valid? ")
if(img.isValid()):
    print("Ok")
    
    imgOut = py.Image()
    
    print("Filtering the image with a Gaussian filter with sigma = 4.0")
    imgOut = py.FilterGaussian2D.execute(img, 4.0)
    imgOut.Write("filtered_gaussian_4_0.hdr")
    
else:
    print("No, the file is not valid!")