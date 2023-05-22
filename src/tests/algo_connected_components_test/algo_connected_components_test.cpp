// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_connected_components_test.cpp -lGL -lGLEW 

//This means that we disable Eigen; some functionalities cannot be used.
//For example, estimating the camera response function
#define PIC_DISABLE_EIGEN
//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{

    printf("Reading an LDR file...");

    pic::Image img;
    img.Read("connected_test.png", pic::LT_NOR);

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid()) {
        printf("Ok\n");

        printf("Computing connected components...");

        std::vector<pic::LabelOutput> ret;
        pic::ConnectedComponents cc;

        float color[] = {0.0f, 0.0f, 0.0f};
        auto mask = img.convertToMask(color, 0.0f, true, NULL);

        pic::Image tmp;
        tmp.convertFromMask(mask, img.width, img.height);

        auto img_cc = cc.execute(mask, img.width, img.height, NULL, ret);

        printf("Ok!\n");


        unsigned int areaMin = img.nPixels();
        for(unsigned int i = 0; i < ret.size(); i++) {
            std::cout<<ret[i].id<<"\n";
            unsigned int areaTmp = ret[i].coords.size();
            if(areaMin > areaTmp) {
                areaMin = areaTmp;
            }
        }

        std::string out = "The size of the smallest circle is: " + pic::fromNumberToString(areaMin) + " pixels.\n";
        printf("%s", out.c_str());

        printf("Writing the connected component labeling results to a file on the disk...");

        pic::Image *comp = pic::ConnectedComponents::convertFromIntegerToImage(img_cc, NULL, img.width, img.height);
        bool bWritten = comp->Write("connected_components.pfm");

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }
    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}
