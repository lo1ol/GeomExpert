#ifndef GEOMLIST_H
#define GEOMLIST_H

#include <memory>
#include "figure3d.h"

namespace figures {

class Node{
public:
    Node();
    Node(Node &prev, std::shared_ptr<figures::Figure3D> &val);

    std::shared_ptr<figures::Figure3D> &operator*();
    const std::shared_ptr<figures::Figure3D> &operator*() const;

protected:
    Node &prev;
    Node &next;
    std::shared_ptr<figures::Figure3D> val;
};

class GeomIterator{
public:
    GeomIterator();
    GeomIterator(Node &);
    GeomIterator &operator--();
    GeomIterator &operator++();
    const GeomIterator &operator--(int);
    const GeomIterator &operator++(int);

private:
    Node &node;
};

class GeomList
{
public:
    typedef std::shared_ptr<figures::Figure3D> elem;

    GeomList();
    void push(const elem &fig);
    elem pop();
    GeomIterator& insert(GeomIterator &iter, const elem&);
    
protected:
    Node root;
};

}

#endif // GEOMLIST_H
