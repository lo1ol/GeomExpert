#include <iostream>
#include "figure3d.h"
#include <list>
#include <memory>

using namespace figures;

int main()
{
    typedef std::unique_ptr<Figure3D> uf_ptr;

    uf_ptr fig(new Cylinder(CylinderParams(1, 2)));
    std::cout<<*fig<<std::endl;
    std::list<uf_ptr> ls;
    ls.push_back(uf_ptr(new Cylinder()));
    ls.push_back(uf_ptr(new Cube()));
    ls.push_back(uf_ptr(new Pyramid(PyramidParams(1, 1))));
    ls.push_back(uf_ptr(new Parallelepiped()));
    for(const auto &elem: ls)
        std::cout<<*elem<<std::endl;
    ls.clear();

    Pyramid fig2 = Pyramid();
    std::cout<<fig2<<std::endl;
    fig2 = Pyramid(PyramidParams(1, 2));
    std::cout<<fig2<<std::endl;
    fig2.setParams(PyramidParams(2, 5));
    std::cout<<fig2<<std::endl;
    std::cin>>fig2;
    std::cout<<fig2<<std::endl;

    uf_ptr fig3(fig2.copy());
    fig2.setParams(PyramidParams(43));
    std::cout<<fig2<<std::endl<<*fig3<<std::endl;

}
