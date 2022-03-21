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
    void printNode() const;

    void setClass(std::string newClass);
    void setColor(sf::Color color);
    void setPercent(int value);
    sf::Color getColor() const;

    std::size_t getSize() const;
    std::string getClass() const;
    short getPercent() const;


public:
    double                  distance = 0;
private:
    std::vector<double>     _attrs;
    std::string             _lastAttr;
    std::size_t             _size;
    sf::Color               _color;
    int                     _percent;
};