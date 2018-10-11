#ifndef GEOMLIST_H
#define GEOMLIST_H

#include <memory>
#include "figure3d.h"

namespace figures {


class GeomList
{
protected: //implementation of node of list
    typedef Figure3D value_type;

    struct Node{
        Node *next; // pointer to the next node (if last, them equal nullptr)
        value_type *val; // pointer to the Figure3D
    };

public:
    GeomList():
        root(nullptr), last(nullptr){ }
    GeomList(const GeomList &);
    GeomList(GeomList &&);
    GeomList &operator=(const GeomList&);
    GeomList &operator=(GeomList &&);
    ~GeomList(){ clear(); }

    void push(const value_type &fig){ push(fig.copy()); } //make a copy from fig
    void push(value_type* const &fig){ push(fig->copy()); } //make a copy from fig if argument was l-value
    void push(value_type* &&fig); //take ownership to itself if argument was r-value
    void clear();
    friend std::ostream &operator<<(std::ostream &os, const GeomList &); // overload operator << to print itself
    std::ostream &print(std::ostream &os) const;
    bool empty() const { return root == nullptr; } // check container is empty
protected:
    Node *root;//pointer to the first element
    Node *last;//pointer to the last element
};


class ExtendedGeomList: public GeomList{
public:
    ExtendedGeomList()=default;
    ExtendedGeomList(const ExtendedGeomList &)=default;
    ExtendedGeomList(ExtendedGeomList &&)=default;
    explicit ExtendedGeomList(const GeomList &other):GeomList(other){} // can called only explicitly
    explicit ExtendedGeomList(GeomList &&other):GeomList(std::move(other)){}
    ExtendedGeomList &operator=(const ExtendedGeomList &)=default;
    ExtendedGeomList &operator=(ExtendedGeomList &&)=default;

    void addAfterEachNth(const value_type &fig, size_t N) {addAfterEachNth(fig.copy(), N);} // the same logic with parametrs
    void addAfterEachNth(value_type* const &fig, size_t N){addAfterEachNth(fig->copy(), N);}
    void addAfterEachNth(value_type* &&fig, size_t N);
};


}

#endif // GEOMLIST_H
