# This program test all Tone Mappes of pyccante


import pyccante as pyc

img0_str = "../_data/input/bottles.hdr"

img0 = pyc.Image(img0_str, pyc.LT_NOR)

print("Tone mapping the input image...")
    
out = pyc.DragoTMO.execute(img0)
out.Write("../_data/output/tone_mapper_drago.png")

out = pyc.DurandTMO.execute(img0)
out.Write("../_data/output/tone_mapper_durand.png")
    
out = pyc.ExposureFusion.execute(img0)
out.Write("../_data/output/tone_mapper_drago.png")

out = pyc.ReinhardTMO.executeGlobal1(img0)
out.Write("../_data/output/tone_mapper_r_global1.png")


out = pyc.ReinhardTMO.executeGlobal2(img0)
out.Write("../_data/output/tone_mapper_r_global2.png")

out = pyc.ReinhardTMO.executeLocal1(img0)
out.Write("../_data/output/tone_mapper_r_local1.png")

out = pyc.ReinhardTMO.executeLocal2(img0)
out.Write("../_data/output/tone_mapper_r_local2.png")

out = pyc.WardHistogramTMO::execute(img0)
out.Write("../_data/output/tone_mapper_ward.png")

out = pyc.FilterSimpleTMO::execute(img0, 1, 1)
out.Write("../_data/output/tone_mapper_simpletmo.png")

print("Ok\n")
