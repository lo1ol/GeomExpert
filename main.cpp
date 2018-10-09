#include <iostream>
#include "figure3d.h"


int main()
{
    figures::Figure3D * fig = new figures::Cylinder;
    std::cin>>*fig;
    std::cout<<*
               fig<<std::endl;
    delete fig;
}
