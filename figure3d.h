#ifndef FIGURE3D_H
#define FIGURE3D_H

#include<iostream>
#include<memory>
#include<string>

namespace figures{

//Abstract class of parametr. Which can be used to set the property of shapes.
//Each class derived from them must implement method of:
//  copy itsself,
//  input its property from stream
//  operator of type convertion to std::string
class Figure3DParams{
public:
    Figure3DParams()=default;
    // we can copy object of this type to the other object
    Figure3DParams(const Figure3DParams &)=default;
    Figure3DParams &operator=(const Figure3DParams &)=default;
    virtual ~Figure3DParams();

    virtual operator std::string() const =0;
    virtual Figure3DParams *copy() const =0;

    //we can set property of this object from streams (for example standards).
    friend std::istream &operator>>(std::istream &is, Figure3DParams &params);
    friend std::ostream &operator<<(std::ostream &os, const Figure3DParams &params);
protected:
    //this methdods used in previous operator overloads
    std::ostream &print(std::ostream &os) const;
    virtual std::istream &input(std::istream &is)=0;
};

//next classes of *Params implement specific classes of Parametrs
//they are contain parametrs of figures and implenetation of pure methods of based abstract class

class Cylinder;

class CylinderParams: public Figure3DParams{
public:
    CylinderParams(double radius=0.5, double height=1.);
    CylinderParams(const CylinderParams&)=default;
    CylinderParams &operator=(const CylinderParams&)=default;
    ~CylinderParams() override=default;

    operator std::string() const final override; // to show its property
    CylinderParams *copy() const final override;
    friend Cylinder; //to get value of shape with this properties
protected:
    std::istream &input(std::istream &is) final override;
private:
    double radius;
    double height;
};

class Parallelepiped;

class ParallelepipedParams: public Figure3DParams{
public:
    ParallelepipedParams(double height=1., double length = 1., double width = 1.);
    ParallelepipedParams(const ParallelepipedParams&)=default;
    ParallelepipedParams &operator=(const ParallelepipedParams&)=default;
    ~ParallelepipedParams() override=default;

    operator std::string() const override;
    ParallelepipedParams *copy() const override;
    friend Parallelepiped;
protected:
    std::istream &input(std::istream &is) override;

    double height;
    double length;
    double width;
};

class Cube;

class CubeParams: public ParallelepipedParams{
public:
    explicit CubeParams(double height=1.):
        ParallelepipedParams (height, height, height){}
    CubeParams(const CubeParams&)=default;
    CubeParams &operator=(const CubeParams&)=default;
    ~CubeParams() override=default;


    operator std::string() const override;
    CubeParams *copy() const override;
    friend Cube;
protected:
    std::istream &input(std::istream &is) override;
};

class Pyramid;

class PyramidParams: public Figure3DParams{
public:
    PyramidParams(double height=1., double innerRadius=0.5, unsigned sideCnt = 4);
    PyramidParams(const PyramidParams&)=default;
    PyramidParams &operator=(const PyramidParams&)=default;
    ~PyramidParams() override=default;

    operator std::string() const override;
    PyramidParams *copy() const override;
    friend Pyramid;
protected:
    std::istream &input(std::istream &is) override;
private:
    double height;
    double innerRadius;
    unsigned sideCnt;
};








class Figure3D{
public:
    Figure3D(const Figure3DParams &params): // constructors to construct itself from recieved params
        Figure3D(params.copy()){} // if params is passed by reference -- make copy of them
    Figure3D(Figure3DParams* const &params): // if params of is l-reference - then params probaly used outside
        Figure3D(params->copy()){}          // then make copy of it
    Figure3D(Figure3DParams* &&params){ setParams(std::move(params)); } // if params of r-reference then probably
                                                                        // owner want to pass ownership
    Figure3D(const Figure3D &other): Figure3D(other.params->copy()){}
    Figure3D(Figure3D &&other):
        params(std::move(other.params)){}
    Figure3D &operator=(const Figure3D &);
    Figure3D &operator=(Figure3D &&);
    virtual ~Figure3D() /*=default*/; // default but not inline. To place vtable in certain translation unit

    const Figure3DParams *getParams() const {return params->copy();} //make copy of params and pass onwership
    void setParams(const Figure3DParams &params){ setParams(params.copy()); } // the same logic as used in construcors
    void setParams(Figure3DParams* const &params){ setParams(params->copy()); }
    void setParams(Figure3DParams* &&params){this->params.reset(params);}
    virtual double volume() const =0;
    virtual Figure3D *copy() const =0;

    friend std::istream &operator>>(std::istream &is, Figure3D &fig);
    friend std::ostream &operator<<(std::ostream &os, const Figure3D &fig);

protected:
    std::unique_ptr<Figure3DParams> params; // to make constuctor default
};


//next classes are obvious
class Cylinder: public Figure3D{
public:
    Cylinder(const CylinderParams &params = CylinderParams()):
        Figure3D(params) {}
    Cylinder(const Cylinder &)=default;
    Cylinder(Cylinder &&)=default;
    Cylinder &operator=(const Cylinder &)=default;
    Cylinder &operator=(Cylinder &&)=default;
    ~Cylinder()final override =default;

    double volume() const final override;
    Cylinder *copy() const final override;
};


class Parallelepiped: public Figure3D{
public:
    Parallelepiped(const ParallelepipedParams &params = ParallelepipedParams()):
        Figure3D(params) {}
    Parallelepiped(const Parallelepiped &)=default;
    Parallelepiped(Parallelepiped &&)=default;
    Parallelepiped &operator=(const Parallelepiped &) =default;
    Parallelepiped &operator=(Parallelepiped &&) =default;
    ~Parallelepiped() override =default;


    double volume() const final override;
    Parallelepiped *copy() const override;
};

class Cube: public Parallelepiped{
public:
    Cube(const CubeParams &params = CubeParams(1.)):
        Parallelepiped (params) {}
    Cube(const Cube &)=default;
    Cube(Cube &&)=default;
    Cube &operator=(const Cube &)=default;
    Cube &operator=(Cube &&)=default;
    ~Cube() final override=default;


    Cube *copy() const final override;
};

class Pyramid: public Figure3D{
public:
    Pyramid(const PyramidParams &params = PyramidParams()):
        Figure3D(params) {}
    Pyramid(const Pyramid &)=default;
    Pyramid(Pyramid &&)=default;
    Pyramid &operator=(const Pyramid &)=default;
    Pyramid &operator=(Pyramid &&)=default;
    ~Pyramid() final override =default;


    virtual double volume() const final override;
    Pyramid *copy() const final override;
};
}

#endif // FIGURE3D_H
