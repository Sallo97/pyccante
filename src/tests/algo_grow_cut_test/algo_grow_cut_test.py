import pyccante as py

img = py.Image()
strokes = py.Image()
img.Read("ye_img.png")
strokes.Read("ye_strokes.png")

seeds = py.GrowCut.fromStrokeImageToSeeds(strokes)

gc_seg = py.GrowCut.execute(img, seeds)
gc_seg.Write("status.pfm")
gc_mask = py.GrowCut.getMaskAsImage(gc_seg)
gc_mask.Write("mask.png")