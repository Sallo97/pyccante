import pyccante as py

# Load hdr_obj
hdr_obj = py.HDRMerger()
hdr_obj.addFile("cannon1.jpg", -2)
hdr_obj.addFile("cannon2.jpg", 0)
hdr_obj.addFile("cannon3.jpg", +2)

# Execute the algorithm
imgOut = hdr_obj.execute()
imgOut.Write("result.hdr")