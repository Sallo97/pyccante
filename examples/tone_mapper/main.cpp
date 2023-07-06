// This program test all Tone Mappes of Piccante


#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img0_str = "../_data/input/bottles.hdr";

    pic::Image img0;
    img0.Read(img0_str, pic::LT_NOR);

    std::cout<<("Tone mapping the input image...");
    
    pic::Image out = pic::DragoTMO::execute(&img0, NULL);
    out.Write("../_data/output/tone_mapper_drago.png");

    out = pic::DurandTMO::execute(&img0, NULL);
    out.Write("../_data/output/tone_mapper_durand.png");
    
    out = pic::ExposureFusion::execute(&img0, NULL);
    out.Write("../_data/output/tone_mapper_drago.png");

    out = pic::ReinhardTMO::executeGlobal1(&img0, NULL);
    out.Write("../_data/output/tone_mapper_r_global1.png");


    out = pic::ReinhardTMO::executeGlobal2(&img0, NULL);
    out.Write("../_data/output/tone_mapper_r_global2.png");

    out = pic::ReinhardTMO::executeLocal1(&img0, NULL);
    out.Write("../_data/output/tone_mapper_r_local1.png");

    out = pic::ReinhardTMO::executeLocal2(&img0, NULL);
    out.Write("../_data/output/tone_mapper_r_local2.png");

    out = pic::WardHistogramTMO::execute(&img0, NULL);
    out.Write("../_data/output/tone_mapper_ward.png");

    out = pic::FilterSimpleTMO::execute(&img0, NULL, 1, 1);
    out.Write("../_data/output/tone_mapper_simpletmo.png");

    printf("Ok\n");
}
