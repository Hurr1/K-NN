#pragma once
#include <vector>
#include <algorithm>
#include "SFML/Graphics.hpp"

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

    double getX() const;
    double getY() const;
    double getW() const;
    double getZ() const;

public:
    double                  distance = 0;
    sf::Color               color;
private:
    std::vector<double>     _attrs;
    std::string             _lastAttr;
    std::size_t             _size;

};