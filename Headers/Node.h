#pragma once
#include <vector>
#include <algorithm>

class Node
{
public:
    Node(std::vector<double> attributes,std::string lastAttr,int size);
    ~Node() = default;

    double at(int index) const;
    void printNode() const ;
    std::size_t getSize() const;
    std::string getClass() const;
    void setClass(std::string newClass);

public:
    double                  distance = 0;
private:
    std::vector<double>     _attrs;
    std::string             _lastAttr;
    std::size_t             _size;

};