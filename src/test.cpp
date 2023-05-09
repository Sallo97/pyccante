#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    pic::Image hello_kitty("../test.png", 
                          pic::LDR_type::LT_NOR);
    
    hello_kitty.scaleCosine();
    hello_kitty.Write("../scaleCosine.png");

}