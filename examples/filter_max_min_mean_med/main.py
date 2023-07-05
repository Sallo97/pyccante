import pyccante as pyc

img_str = "../_data/input/tommaseo_statue.png"

print("Reading image...")
img = pyc.Image(img_str, pyc.LDR_type.LT_NOR_GAMMA)
print("Ok")

print("Is it valid?")
if img.isValid():
    print("Ok")
    
    # Applying FilterMax
    print("Filtering the image with the Max filter (radius of 3);\n")
    output = pyc.FilterMax.execute(img, 7)
    output.Write("../_data/output/Filter_Max.png", pyc.LDR_type.LT_NOR_GAMMA)
    print("Ok!\n")

    # Applying FilterMin
    print("Filtering the image with the Min filter (radius of 3);\n")
    output = pyc.FilterMin.execute(img, 7)
    output.Write("../_data/output/Filter_Min.png", pyc.LDR_type.LT_NOR_GAMMA)
    print("Ok!\n")
        
    # Applying FilterMean
    print("Filtering the image with the Mean filter (radius of 3);\n")
    output = pyc.FilterMean.execute(img, 7)
    output.Write("../_data/output/Filter_Mean.png", pyc.LDR_type.LT_NOR_GAMMA)
    print("Ok!\n")
        
    # Applying FilterMed
    print("Filtering the image with the Median filter (radius of 3);\n")
    output = pyc.FilterMed.execute(img, 7)
    output.Write("../_data/output/Filter_Med.png", pyc.LDR_type.LT_NOR_GAMMA)
    print("Ok!\n")    
else:
    print("No, the image is not valid!")