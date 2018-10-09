#include "figure3d.h"
#include <cmath>
#include <iostream>
#include <exception>

namespace figures{

std::istream &operator>>(std::istream &is, Figure3D &fig){ return fig.input(is); }
std::ostream &operator<<(std::ostream &os, const Figure3D &fig){ return fig.print(os)<<"\n\tvolume: "<<fig.volume(); }


Figure3D::~Figure3D(){}


Cylinder::Cylinder(double radius, double height): Figure3D(){
    setRadius(radius);
    setHeight(height);
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
    double r, h;
    std::cout<<"Input radius: ";
    if(!(is>>r)){
        return is;
    }
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    setRadius(r);
    setHeight(h);
    return is;
}


void Cylinder::setRadius(double value){
    if(value<0){
        throw std::runtime_error("Bad radius. Must be non-negative");
    }
    else{
        radius =value;
    }
}

double Cylinder::getRadius() const{
    return radius;
}

void Cylinder::setHeight(double value){
    if(value<0){
        throw std::runtime_error("Bad height. Must be non-negative");
    }
    else{
        height =value;
    }
}

double Cylinder::getHeight() const{
    return height;
}


Parallelepiped::Parallelepiped(double height, double length, double width): Figure3D(){
    setHeight(height);
    setLength(length);
    setWidth(width);
}

/*virtual*/ double Parallelepiped::volume() const
{
    return height*length*width;
}

/*virtual*/ Parallelepiped *Parallelepiped::copy() const
{
    return new Parallelepiped(*this);
}

bool Parallelepiped::isCube() const
{
    return height == length and length == width;
}

void Parallelepiped::makeCube(double value)
{
    setHeight(value);
    length=width=value;
}


double Parallelepiped::getHeight() const
{
    return height;
}

void Parallelepiped::setHeight(double value)
{
    if(value<0){
        throw std::runtime_error("Bad height. Must be non-negative");
    }
    else{
        height = value;
    }
}

double Parallelepiped::getLength() const
{
    return length;
}

void Parallelepiped::setLength(double value)
{
    if(value<0){
        throw std::runtime_error("Bad length. Must be non-negative");
    }
    else{
        length = value;
    }
}

double Parallelepiped::getWidth() const
{
    return width;
}

void Parallelepiped::setWidth(double value)
{
    if(value<0){
        throw std::runtime_error("Bad width. Must be non-negative");
    }
    else{
        width = value;
    }
}

/*virtual*/ std::ostream &Parallelepiped::print(std::ostream &os) const
{
    return os<<"Parallelepiped: "
      <<"\n\theight: "<<height
      <<"\n\tlength: "<<length
     <<"\n\twidth: "<<width;
}

/*virtual*/ std::istream &Parallelepiped::input(std::istream &is){
    double h, l, w;
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
    setHeight(h);
    setLength(l);
    setWidth(w);
    return is;
}

Cube::Cube(double height): Parallelepiped ()
{
    this->makeCube(height);
}

/*explicit*/ Cube::Cube(const Parallelepiped & other)
{
    std::cout<<"constrctorFromParal\n";
    if(other.isCube()){
        makeCube(other.getHeight());
    }
    else{
        throw std::runtime_error("This Parallelepiped isn't cube");
    }
}

/*virtual*/ Cube *Cube::copy() const
{
    return new Cube(*this);
}

/*virtual*/ std::ostream &Cube::print(std::ostream &os) const
{
    return os<<"Cube:"
     <<"\n\theight: "<<height;
}

/*virtual*/ std::istream &Cube::input(std::istream &is)
{
    double h;
    std::cout<<"Input height: ";
    if(!(is>>h)){
        return is;
    }
    setHeight(h);
    return is;
}

Pyramid::Pyramid(double height, double inner_radius, unsigned side_cnt):Figure3D(){
    setHeight(height);
    setInnerRadius(inner_radius);
    setSideCnt(side_cnt);
    }

/*virtual*/ double Pyramid::volume() const
    {
        return (height*innerRadius/6)*sideCnt;
    }

/*virtual*/ Pyramid *Pyramid::copy() const
    {
        return new Pyramid(*this);
    }

double Pyramid::getHeight() const
    {
        return height;
    }

void Pyramid::setHeight(double value)
    {
        if(value<0){
            throw std::runtime_error("Bad width. Must be non-negative");
        }
        else{
            height = value;
        }
    }

double Pyramid::getInnerRadius() const
    {
        return innerRadius;
    }

void Pyramid::setInnerRadius(double value)
    {
        if(value<0){
            throw std::runtime_error("Bad width. Must be non-negative");
        }
        else{
            innerRadius = value;
        }
    }

unsigned Pyramid::getSideCnt() const
    {
        return sideCnt;
    }

void Pyramid::setSideCnt(const unsigned &value){

    if(value<=2){
        throw std::runtime_error("Bad side number. Must be more then 2");
    }
    else{
        sideCnt = value;
    }
}

/*virtual*/ std::ostream &Pyramid::print(std::ostream &os) const
    {
        return os<<"Pyramid: "
          <<"\n\theight: "<<height
          <<"\n\tinner radius: "<<innerRadius
         <<"\n\tside number: "<<sideCnt;
    }

/*virtual*/ std::istream &Pyramid::input(std::istream &is)
    {
        double h, r;
        unsigned c;
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
        setHeight(h);
        setInnerRadius(r);
        setSideCnt(c);
        return is;
    }

}
