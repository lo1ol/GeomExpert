#include "geomlist.h"

namespace figures {

GeomList::GeomList(const GeomList &other):
    GeomList()
{
    if(other.root != nullptr){ // check that other ifs not empty
        last = root = new Node{nullptr, other.root->val->copy()}; //  inizialize root. make last same

            // copy untill go to the last node (nullptr)
        for(auto otherNode = other.root->next /*take next node*/; otherNode != nullptr; otherNode = otherNode->next){
            last = last->next = new Node{nullptr, otherNode->val->copy()}; // create new Node from copy of val and nullptr's next Node
        }
    }
}

GeomList::GeomList(GeomList &&other):
    root(other.root), last(other.last)
{
    other.root = other.last = nullptr; //keep other correct
}

GeomList &GeomList::operator=(const GeomList &other)
{
    if(this != &other){ // optimisatin for same object
        auto temp(other); //construct new from other
        this->clear(); //clear after copy to keep correct this if error occured
        *this = std::move(temp); // move temp
    }
    return *this;
}

GeomList &GeomList::operator=(GeomList &&other)
{
    if(this != &other){ //
        this->clear(); // clear previous state
        root = other.root;
        last = other.last;
        other = GeomList(); // keep other correct
    }
    return *this;
}

void GeomList::push(GeomList::value_type * &&fig)
{
    if(root == nullptr){ // if first node
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
    while(root!=nullptr){ //clear itself deleting consistently
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
    while (curNode != nullptr) { //until go to the last
        if(++i % N == 0){ //if Nth insert copy
            auto nextNode = curNode->next;  // keep next Node
            curNode->next = new Node{nextNode, fig->copy()}; //create new Node and bind to the current node
            curNode = curNode->next; // go on
        }
        curNode = curNode->next;
    }
    delete fig; // delete object which we use to make copy
}
}
