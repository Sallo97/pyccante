# This program test Image.blend feature of pyccante

import pyccante as pyc

img_str = "../_data/input/venice.png"
blend_str = "../_data/input/blend/flower_to_blend.png"
weight_str = "../_data/input/blend/blend_mask.png"


print("Reading image...")
img = pyc.Image(img_str, pyc.LDR_type.LT_NOR_GAMMA)

blend = pyc.Image(blend_str, pyc.LDR_type.LT_NOR_GAMMA)

weight = pyc.Image(weight_str, pyc.LDR_type.LT_NOR_GAMMA)
print("Ok")

print("Is it valid?")
if img.isValid():
    print("Ok")

    # Applying Blend
    print("Applying blend...")
    img.blend(blend, weight)
    img.Write("../_data/output/blend.png", pyc.LDR_type.LT_NOR_GAMMA)
    print("Ok!")

else:
    print("No, the image is not valid!")
