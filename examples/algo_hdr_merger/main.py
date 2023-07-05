# This program test HDRMerger of pyccante

import pyccante as pyc


print("Adding file names to the merger...\n")
merger = pyc.HDRMerger()

for i in range(7): 
    name = "../_data/input/stack/stack_room_exp_" + pyc.fromNumberToString(i) + ".jpg";
        
    info = pyc.getJPGExposure(name) 
    merger.addFile(name, info.exposureTime);

print("Ok");

print("Merging LDR images into an HDR image...");
imgOut = merger.execute()
print("Ok");

if(imgOut.isValid()) {
        if(imgOut->isValid()) {
            imgOut->Write("../_data/output/image_debevec_crf.hdr");
            pic::Image *imgTmo = pic::ReinhardTMO::executeGlobal1(imgOut, NULL);
            imgTmo->Write("../_data/output/image_debevec_crf_tmo.png", pic::LT_NOR_GAMMA);

        }
    }

    return 0;
}