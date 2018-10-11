#include "geomlist.h"

namespace figures {

GeomList::GeomList(const GeomList &other):
    GeomList()
{
    if(other.root != nullptr){
        last = root = new Node{nullptr, other.root->val->copy()};

        for(auto otherNode = other.root->next; otherNode != nullptr; otherNode = otherNode->next){
            last->next = new Node{nullptr, otherNode->val->copy()};
            last = last->next;
        }
    }
}

GeomList::GeomList(GeomList &&other):
    root(other.root), last(other.last)
{
    other.root = other.last = nullptr;
}

GeomList &GeomList::operator=(const GeomList &other)
{
    if(this != &other){
        auto temp(other);
        *this = std::move(temp);
    }
    return *this;
}

GeomList &GeomList::operator=(GeomList &&other)
{
    if(this != &other){
        this->clear();
        root = other.root;
        last = other.last;
        other = GeomList();
    }
    return *this;
}

void GeomList::push(GeomList::value_type * &&fig)
{
    if(root == nullptr){
        root = new Node{nullptr, fig};
        last = root;
    }
    else{
        last->next = new Node{nullptr, fig};
        last = last->next;
    }
}

void GeomList::clear()
{
    while(root!=nullptr){
        auto nextNode = root->next;
        delete root->val;
        delete root;
        root = nextNode;
    }
    last = nullptr;
}

std::ostream &operator<<(std::ostream &os, const GeomList &ls)
{
    return ls.print(os);
}

std::ostream &GeomList::print(std::ostream &os) const
{
    auto curNode = root;
    while(curNode != nullptr){
        os<<*curNode->val<<"\n"<<std::endl;
        curNode = curNode->next;
    }
    return os;
}

void ExtendedGeomList::addAfterEachNth(value_type* &&fig, size_t N)
{
    size_t i = 0;
    auto curNode = root;
    while (curNode != nullptr) {
        if(++i % N == 0){
            auto nextNode = curNode->next;
            curNode->next = new Node{nextNode, fig->copy()};
            curNode = curNode->next;
        }
        curNode = curNode->next;
    }
    delete fig;
}
}
