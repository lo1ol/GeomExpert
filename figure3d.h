#ifndef FIGURE3D_H
#define FIGURE3D_H

#include<iostream>

namespace figures{

class Figure3D{
public:
    Figure3D()=default;
    Figure3D(const Figure3D &)=default;
    Figure3D(Figure3D &&)=default;
    virtual ~Figure3D();

    virtual double volume() const =0;
    virtual Figure3D *copy() const =0;

private:
    virtual std::ostream &print(std::ostream &os) const =0;
    virtual std::istream &input(std::istream &is)=0;
    friend std::istream &operator>>(std::istream &is, Figure3D &fig);
    friend std::ostream &operator<<(std::ostream &os, const Figure3D &fig);
};



class Cylinder: public Figure3D{
public:
    Cylinder(double radius=0.5, double height=1.);
    Cylinder(const Cylinder&)=default;
    ~Cylinder()final override =default;

    double volume() const final override;
    Cylinder *copy() const final override;

    double getRadius() const;
    void setRadius(double value);

    double getHeight() const;
    void setHeight(double value);

private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;

    double radius;
    double height;
};

class Cube;

class Parallelepiped: public Figure3D{
public:
    Parallelepiped(double height = 1., double length =1., double width =1.);
    Parallelepiped(const Parallelepiped&)=default;
    ~Parallelepiped() override =default;

    double volume() const final override;
    Parallelepiped *copy() const override;

    bool isCube() const;
    void makeCube(double value);

    double getHeight() const;
    void setHeight(double value);

    double getLength() const;
    void setLength(double value);

    double getWidth() const;
    void setWidth(double value);

private:
    std::ostream &print(std::ostream &os) const override;
    std::istream &input(std::istream &is) override;
protected:
    double height;
    double length;
    double width;
};

class Cube: public Parallelepiped{
public:
    Cube(double height = 1.);
    Cube(const Cube &)=default;
    explicit Cube(const Parallelepiped &);
    ~Cube() final override=default;

    Cube *copy() const final override;


    void setHeight(double value){ makeCube(value); }
    void setLength(double value){ makeCube(value); }
    void setWidth(double value){ makeCube(value); }
private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;
};

class Pyramid: public Figure3D{
public:
    Pyramid(double height = 1., double innerRadius =0.5, unsigned sideCnt = 4);
    Pyramid(const Pyramid &)=default;
    ~Pyramid() final override =default;

    virtual double volume() const final override;
    Pyramid *copy() const final override;

    double getHeight() const;
    void setHeight(double value);

    double getInnerRadius() const;
    void setInnerRadius(double value);

    unsigned getSideCnt() const;
    void setSideCnt(const unsigned &value);

private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;

    double height;
    double innerRadius;
    unsigned sideCnt;

};
}

#endif // FIGURE3D_H
