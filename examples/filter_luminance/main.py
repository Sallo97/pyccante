# This program test the FilterLuminance of pyccante


import pyccante as pyc

img0_str = "../_data/input/balcony_0.png"
    
print("Reading LDR images...")
img0 = pyc.Image(img0_str, pyc.LDR_type.LT_NOR)
    
print("Ok\n");

print("Is it valid? ")
if img0.isValid() :

    print("OK\n")

    # compute the luminance images
    print("Applying FilterLuminance\n")
    L0 = pyc.FilterLuminance.execute(pyc.LDR_type.LT_CIE_LUMINANCE)
    L0.Write("../_data/output/filter_luminance.png", pyc.LDR_type.LT_NOR)
    print("OK\n");
    
else: 
    printf("No, it is not valid!\n")
