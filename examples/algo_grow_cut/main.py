# This program test the GrowCut algorithm of pyccante

import pyccante as pyc

print("Reading an image...")

img_str = "../_data/input/yellow_flowers.png"
strokes_str = "../_data/input/yellow_flowers_segmentation_strokes.png"
    
img = pyc.Image(img_str)
strokes = pyc.Image(strokes_str)

print("OK\n")

print("Are input images valid? ")
if img.isValid() and strokes.isValid():
    print("OK\n")
        
    seeds = pyc.GrowCut.fromStrokeImageToSeeds(strokes)

    if seeds != None:
        gc_seg = pyc.GrowCut.execute(seeds)
        
        gc_seg.Write("../_data/output/grow_cut_status.pfm")

        gc_mask = pyc.GrowCut.getMaskAsImage(gc_seg)

        gc_mask.Write("../_data/output/grow_cut_mask.png")

    else:    
        print("No, the seeds image is not valid!")

else :
    print("No, the file is not valid!")
    