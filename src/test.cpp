#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    std::cout<<"creating the Image obj\n";

    pic::Image hello_kitty();
    
    std::cout<<"doing flipH()\n";
    hello_kitty->flipH();
    std::cout<<"doing flipV()\n";
    hello_kitty.flipV();
    std::cout<<"doing flipHV()\n";
    hello_kitty.flipHV();
    std::cout<<"doing flipVH()\n";
    hello_kitty.flipVH();
    hello_kitty.Write("../all_flips.png");

}