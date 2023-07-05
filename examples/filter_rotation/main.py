#This program test the FilterRotation of pyccante


import pyccante as pyc


img_str = "../_data/input/cs_warwick.hdr"
    

print("Reading a 360 panoramic image file...")

img = pyc.Image(img_str)

print("Ok\n")

print("Is it valid? ")
if img.isValid():
    print("OK\n")

    img_rot_simple = pyc.FilterRotation.execute(0, 1,5708 , 0)
    img_rot_simple.Write("../_data/output/rotation.hdr")
    img_tone_map = pyc.DragoTMO.execute(img_rot_simple)
    img_tone_map.Write("../_data/output/rotation_tone_map.png")
