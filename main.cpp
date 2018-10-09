#include <iostream>
#include "figure3d.h"


int main()
{
    figures::Figure3D * fig;
    try{
     fig = new figures::Pyramid(1);
    }
    catch(...){
        std::cout<<"kek\n";
    }
    if(!(std::cin>>*fig)){
        std::cout<<"BAD input!\n";
    }
    else{
        //dynamic_cast<figures::Cylinder *>(fig)->setRadius(3);
        std::cout<<*fig<<std::endl;
    }
    delete fig;
}
