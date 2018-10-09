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
    virtual ~Figure3D();

    virtual double volume() const =0;
    virtual Figure3D *copy() const =0;
    virtual void assign(const Figure3D &other)=0;
    virtual void move(Figure3D &&other)=0;

private:
    virtual std::ostream &print(std::ostream &os) const =0;
    virtual std::istream &input(std::istream &is)=0;
    friend std::istream &operator>>(std::istream &is, Figure3D &fig){ return fig.input(is); }
    friend std::ostream &operator<<(std::ostream &os, const Figure3D &fig){ return fig.print(os)<<"\n\tvolume: "<<fig.volume(); }
};



class Cylinder: public Figure3D{
public:
    Cylinder(double radius=0.5, double height=1.);
    Cylinder(const Cylinder&)=default;
    ~Cylinder()final override =default;

    double volume() const final override;
    Cylinder *copy() const final override;
    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override{ assign(other); }

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
    void assign(const Figure3D &other) override;
    void move(Figure3D &&other) override { assign(other); }

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
    ~Cube() final override=default;

    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override { assign(other); }
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
    void assign(const Figure3D &other) final override;
    void move(Figure3D &&other) final override { assign(other); }

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
