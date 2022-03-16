#include <iostream>
#include <utility>
#include "Node.h"

Node::Node(std::vector<double> attrs,std::string lastAttr,int size)
    : _attrs(std::move(attrs)), _lastAttr(std::move(lastAttr)),_size(size){};

double Node::at(int index) const
{
    if(index >= this->_size)
    {
        std::cout<<"Error incorrect index"<<'\n';
        system(EXIT_SUCCESS);
    }
    return this->_attrs.at(index);
}


void Node::printNode() const
{
    for(double i : _attrs)
        std::cout<<"["<<i<<']';
    std::cout<<"["<<_lastAttr<<']'<<'\n';
}

std::size_t Node::getSize() const {
    return this->_size;
}




