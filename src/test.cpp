#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    pic::Image hello_kitty = new pic::Image();
    
    hello_kitty.scaleCosine();
    hello_kitty.Write("../scaleCosine.png");

}