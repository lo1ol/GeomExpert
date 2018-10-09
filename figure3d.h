#ifndef FIGURE3D_H
#define FIGURE3D_H

#include<iostream>

namespace figures{

class Figure3D{
public:
    Figure3D()=default;
    Figure3D(const Figure3D &)=default;
    Figure3D(Figure3D &&)=default;
    Figure3D &operator=(const Figure3D &other);
    Figure3D &operator=(Figure3D &&other);
    virtual ~Figure3D() /*=default*/; //default but don't inline

    virtual double volume() const =0;
    virtual Figure3D *copy() const =0;
    virtual void assign(const Figure3D &other)=0;
    virtual void move(Figure3D &&other)=0;

private:
    virtual std::ostream &print(std::ostream &os) const =0;
    virtual std::istream &input(std::istream &is)=0;
    friend std::istream &operator>>(std::istream &is, Figure3D &fig){ return fig.input(is); }
    friend std::ostream &operator<<(std::ostream &os, const Figure3D &fig){ return fig.print(os)<<"\n\t volume"<<fig.volume(); }
};



class Cylinder: public Figure3D{
public:
    Cylinder(double radius=0.5, double height=1.):
        Figure3D(), radius(radius), height(height){}
    Cylinder(const Cylinder&)=default;
    ~Cylinder()final override =default;

    double volume() const final override;
    Cylinder *copy() const final override;
    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override{ assign(other); }

private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;

    double radius;
    double height;
};

class Parallelepiped: public Figure3D{
public:
    Parallelepiped(double height = 1., double length =1., double width =1.):
        Figure3D(), height(height), length(length), width (width){}

    ~Parallelepiped() override =default;

    double volume() const final override;
    Parallelepiped *copy() const final override;
    void assign(const Figure3D &other) override;
    void move(Figure3D &&other) override { assign(other); }
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
    Cube(double height = 1.):
        Parallelepiped(height, height, height){}

    ~Cube() final override=default;

    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override { assign(other); }

private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;
};

class Pyramid: public Figure3D{
public:
    Pyramid(double height = 1., double inner_radius =0.5, unsigned side_cnt = 4):
        Figure3D(), height(height), inner_radius(inner_radius), side_cnt(side_cnt){}

    ~Pyramid() final override =default;

    virtual double volume() const final override;
    Pyramid *copy() const final override;
    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override { assign(other); }
private:
    std::ostream &print(std::ostream &os) const final override;
    std::istream &input(std::istream &is) final override;

    double height;
    double inner_radius;
    unsigned side_cnt;

};
}

#endif // FIGURE3D_H
