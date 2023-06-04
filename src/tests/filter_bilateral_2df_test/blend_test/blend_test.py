import pyccante as pyc

blend = pyc.Image("blend.png", pyc.LDR_type.LT_NONE)
to_blend = pyc.Image("to_blend.png", pyc.LDR_type.LT_NONE)
weight = pyc.Image("weight.png", pyc.LDR_type.LT_NONE)

blend.blend(to_blend, weight)
blend.Write("blended.png", pyc.LDR_type.LT_NONE)