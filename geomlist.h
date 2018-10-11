#ifndef GEOMLIST_H
#define GEOMLIST_H

#include <memory>
#include "figure3d.h"

namespace figures {


class GeomList
{
protected:
    typedef figures::Figure3D value_type;

    struct Node{
        Node *next;
        value_type *val;
    };

public:
    GeomList():
        root(nullptr), last(nullptr){ }
    GeomList(const GeomList &);
    GeomList(GeomList &&);
    GeomList &operator=(const GeomList&);
    GeomList &operator=(GeomList &&);
    ~GeomList(){ clear(); }

    void push(const value_type &fig){ push(fig.copy()); }
    void push(value_type* const &fig){ push(fig->copy()); } //doesn't ownership to itself
    void push(value_type* &&fig); //take ownership to itself
    void clear();
    friend std::ostream &operator<<(std::ostream &os, const GeomList &);
    std::ostream &print(std::ostream &os) const;
    bool empty() const { return root == nullptr; }
protected:
    Node *root;
    Node *last;
};


class ExtendedGeomList: public GeomList{
public:
    ExtendedGeomList()=default;
    ExtendedGeomList(const ExtendedGeomList &)=default;
    ExtendedGeomList(ExtendedGeomList &&)=default;
    explicit ExtendedGeomList(const GeomList &other):GeomList(other){}
    explicit ExtendedGeomList(GeomList &&other):GeomList(std::move(other)){}
    ExtendedGeomList &operator=(const ExtendedGeomList &)=default;
    ExtendedGeomList &operator=(ExtendedGeomList &&)=default;

    void addAfterEachNth(const value_type &fig, size_t N) {addAfterEachNth(fig.copy(), N);}
    void addAfterEachNth(value_type* const &fig, size_t N){addAfterEachNth(fig->copy(), N);}
    void addAfterEachNth(value_type* &&fig, size_t N);
};


}

#endif // GEOMLIST_H
