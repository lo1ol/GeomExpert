#include "figure3d.h"
#include <cmath>
#include <iostream>

using namespace figures;




Figure3D &Figure3D::operator=(const Figure3D &other){
    this->assign(other);
    return *this;
}

Figure3D &Figure3D::operator=(Figure3D &&other){
    this->move(static_cast<Figure3D &&>(other));
    return *this;
}

Figure3D::~Figure3D(){}

/*virtual*/ void Cylinder::assign(const Figure3D &other){
    const Cylinder &other_cyl = dynamic_cast<const Cylinder &>(other); //throw bad_cast if other dynanic type not contain Cylinder type part
    radius = other_cyl.radius;
    height = other_cyl.height;
}


/*virtual*/ double Cylinder::volume() const{
    return radius*radius*M_PI*height;
}

/*virtual*/ Cylinder *Cylinder::copy() const{
    return new Cylinder(*this);
}

/*virtual*/  std::ostream &Cylinder::print(std::ostream &os) const{
    return os<<"Cylinder:"
             <<"\n\t radius: "<<radius
             <<"\n\t height: "<<height;
}

/*virtual*/ std::istream &Cylinder::input(std::istream &is){
    std::cout<<"Input radius: ";
    if(!(is>>radius)){
        return is;
    }
    std::cout<<"Input height: ";
    if(!(is>>height)){
        return is;
    }
    return is;
}

