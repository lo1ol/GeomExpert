#include <iostream>
#include "figure3d.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace figures;

std::ostream &operator<<(std::ostream &os, const Figure3D *fig){
    return os<<*fig;
}

int main()
{
    std::list<Figure3D *> ls;
    ls.push_back(new Cube(1.5));
    ls.push_back(new Parallelepiped(1.2, 1.4, 2.));
    ls.push_back(new Cylinder());
    ls.push_front(new Pyramid(1, 4, 5));
    for(const auto fig: ls){
        std::cout<<fig<<std::endl;
    }
    for(auto fig : ls){
        delete fig;
    }
    ls.clear();
    Cube cube((Parallelepiped()));
}
