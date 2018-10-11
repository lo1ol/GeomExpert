#include "figure3d.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <memory>
#include <string>

//used to make easeare implement class method of copy itself

#define MAKE_COPY_METHOD_OF(myclass) \
myclass *myclass::copy() const \
{ \
    return new myclass(*this); \
} \



namespace figures{


std::istream &operator>>(std::istream &is, Figure3DParams &params)
{
    return params.input(is);
}

std::ostream &operator<<(std::ostream &os, const Figure3DParams &params)
{
    return params.print(os);
}




Figure3DParams::~Figure3DParams(){}

std::ostream &Figure3DParams::print(std::ostream &os) const{
    return os<<std::string(*this);
}



CylinderParams::CylinderParams(double radius, double height){
    if(radius>=0. && height>=0.){
        this->radius =radius;
        this->height = height;
    }else
        throw std::runtime_error("Bad arguments");
}

/*virtual*/ CylinderParams *CylinderParams::copy()const {
    return new CylinderParams(*this);
}

/*virtual*/  CylinderParams::operator std::string() const{
    return "Cylinder:"
            "\n\t radius: " + std::to_string(radius)+
            "\n\t height: " + std::to_string(height);
}

/*virtual*/ std::istream &CylinderParams::input(std::istream &is){
    double r, h;
    std::cout<<"Hello, I'm Cylinder"<<std::endl;
    std::cout<<"Input radius: ";
    if(!(is>>r)){
        return is;
    }
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    *this = CylinderParams(r, h);
    return is;
}




ParallelepipedParams::ParallelepipedParams(double height, double length, double width){
    if(height>=0. && length>=0. && width>=0.){
        this->height = height;
        this->length =length;
        this->width = width;
    }else
        throw std::runtime_error("Bad arguments");
}

/*virtual*/ ParallelepipedParams *ParallelepipedParams::copy()const {
    return new ParallelepipedParams(*this);
}

/*virtual*/  ParallelepipedParams::operator std::string() const{
    return "Parallelepiped:"
            "\n\t height: " + std::to_string(height)+
            "\n\t length: " + std::to_string(length)+
            "\n\t width: " + std::to_string(width);
}

/*virtual*/ std::istream &ParallelepipedParams::input(std::istream &is){
    double h, l, w;
    std::cout<<"Hello, I'm Parallelepiped"<<std::endl;
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    std::cout<<"Input length: ";
    if(!(is>>l)){
        return is;
    }
    std::cout<<"Input width: ";
    if(!(is>>w)){
        return is;
    }
    *this = ParallelepipedParams(h, l, w);
    return is;
}




/*virtual*/ CubeParams *CubeParams::copy()const {
    return new CubeParams(*this);
}

/*virtual*/  CubeParams::operator std::string() const{
    return "Cube:"
            "\n\t height: " + std::to_string(height);
}

/*virtual*/ std::istream &CubeParams::input(std::istream &is)
{
    double h;
    std::cout<<"Hello, I'm Cube"<<std::endl;
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    *this = CubeParams(h);
    return is;
}





PyramidParams::PyramidParams(double height, double innerRadius, unsigned sideCnt){
    if(height>=0. && innerRadius>=0. && sideCnt>=3){
        this->height = height;
        this->innerRadius = innerRadius;
        this->sideCnt =sideCnt;
    }else
        throw std::runtime_error("Bad arguments");
}

/*virtual*/ PyramidParams *PyramidParams::copy()const {
    return new PyramidParams(*this);
}

/*virtual*/  PyramidParams::operator std::string() const{
    return "Pyramid:"
            "\n\t height: " + std::to_string(height)+
            "\n\t inner radius: " + std::to_string(innerRadius)+
            "\n\t number of sides: " + std::to_string(sideCnt);
}

/*virtual*/ std::istream &PyramidParams::input(std::istream &is){
    double h, r;
    unsigned c;
    std::cout<<"Hello, I'm Pyramid"<<std::endl;
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    std::cout<<"Input inner radius: ";
    if(!(is>>r)){
        return is;
    }
    std::cout<<"Input side number: ";
    if(!(is>>c)){
        return is;
    }
    *this = PyramidParams(h, r, c);
    return is;
}




Figure3D &Figure3D::operator=(const Figure3D &other)
{
    params.reset(other.params->copy()); //free previous allocated memory for parametrs
                                        //and set new from the copy of other
    return *this;
}

Figure3D &Figure3D::operator=(Figure3D &&other)
{
    params = std::move(other.params); // parametrs of other are correct and cotain nullptr
    return *this;
}

Figure3D::~Figure3D(){}



std::istream &operator>>(std::istream &is, Figure3D &fig){
    return is>>*fig.params;
}
std::ostream &operator<<(std::ostream &os, const Figure3D &fig){
    return os<<*fig.params
             <<"\n\t Volume: "<<fig.volume();
}





/*virtual*/ double Cylinder::volume() const{
    auto p = dynamic_cast<CylinderParams &>(*params);
    return p.radius*p.radius*M_PI*p.height;
}

MAKE_COPY_METHOD_OF(Cylinder) // implementation of Cylinder *Cylinder::copy();





/*virtual*/ double Parallelepiped::volume() const
{
    auto p = dynamic_cast<ParallelepipedParams &>(*params);
    return p.height*p.length*p.width;
}

MAKE_COPY_METHOD_OF(Parallelepiped)


MAKE_COPY_METHOD_OF(Cube)




/*virtual*/ double Pyramid::volume() const{
    auto p = dynamic_cast<PyramidParams &>(*params);
    return (p.height*p.innerRadius/6)*p.sideCnt;
}

MAKE_COPY_METHOD_OF(Pyramid)

}
