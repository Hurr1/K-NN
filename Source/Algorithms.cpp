#pragma once

#include <complex>
#include "../Headers/Node.h"
#include "../Headers/Algorithms.h"
#include "../Headers/CSVRow.h"


std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

std::vector<Node> ai::createDB(std::istream& str)
{
    CSVRow row;
    std::vector<Node> data;
    std::vector<double>toAdd;
    while(str >> row)
    {
        for(int i = 0; i< row.size()-1;i++)
            toAdd.emplace_back(std::stod(row[i]));
        data.emplace_back(Node(toAdd,row[row.size()-1],row.size()));
        toAdd.clear();
    }
    return data;
}

std::vector<Node> ai::createTestDB(std::ifstream& str)
{
        CSVRow row;
        std::vector<Node> data;
        std::vector<double>toAdd;

        while(str >> row)
        {
            for(int i = 0; i< row.size()-1;i++)
                toAdd.emplace_back(std::stod(row[i]));
            data.emplace_back(Node(toAdd,"UNDEFIEND",row.size()));
            toAdd.clear();
        }
        return data;
}

void ai::countDistance(Node& first, Node& second)
{
    double distance = 0;
    for(int i =0;i< first.getSize()-1;i++)
        distance = distance +  std::pow(first.at(i)-second.at(i),2);
    second.distance = distance;
}

void ai::findClass(std::vector<Node> &data, Node &node, int knn, std::vector<Node> &copy, int begin)
{
    if(knn+begin > copy.size())
        knn = copy.size();
    std::vector<pair> vec = ai::makeVector(copy,begin,knn);
    if(vec.size()==1)
    {
        ai::printVec(vec);
        node.setClass(vec.at(0).first);
        node.printNode();
        node.setPercent(100);
        std::cout<<"Accuracy 100%"<<'\n'<<'\n';
        data.push_back(node);
    }
    else if( vec.at(0).second == vec.at(1).second && (begin < data.size() && knn < data.size()))
    {
        ai::findClass(data,node,knn,copy,begin+knn);
    }
    else if( vec.at(0).second > vec.at(1).second)
    {
        ai::printVec(vec);
        node.setClass(vec.at(0).first);
        int sum = 0;
        std::for_each(vec.begin(),vec.end(),[&sum](pair& p){sum = sum + p.second;});
        node.printNode();
        node.setPercent(static_cast<int>((vec.at(0).second * 100)/sum));
        std::cout<<"Accuracy: " << static_cast<int>((vec.at(0).second * 100)/sum)<<'%'<<'\n'<<'\n';
        data.push_back(node);
    }
    else
    {
        printVec(vec);
        node.setClass(vec.at(0).first);
        int sum = 0;
        std::for_each(vec.begin(),vec.end(),[&sum](pair& p){sum = sum + p.second;});
        node.printNode();
        node.setPercent(static_cast<int>((vec.at(0).second * 100)/sum));
        std::cout<<"Accuracy: " << static_cast<int>((vec.at(0).second * 100)/sum)<<'%'<<'\n'<<'\n';
        data.push_back(node);

    }
}

void ai::knnAlgorithm(std::vector<Node>& dataBase, std::vector<Node> testDataBase, int k)
{

    for(Node& test_n : testDataBase)
    {
        for (Node &data_n: dataBase)
            countDistance(test_n, data_n);
        std::vector<Node> copy(dataBase);
        std::sort(copy.begin(),
                  copy.end(),
                  [](const auto& _1, const auto& _2) { return _1.distance < _2.distance; });

        ai::findClass(dataBase, test_n, k, copy);
    }
}

void ai::printVec(const std::vector<pair>&vec)
{
    for (auto const &pair: vec)
        std::cout << '{' << pair.first << "," << pair.second << '}';
    std::cout<<'\n';
}

std::vector<pair> ai::makeVector(std::vector<Node>& data, int begin , int knn)
{
    std::unordered_map<std::string ,int>map;
    if(begin+knn>data.size())
        begin = data.size()-knn;

    for(int i=begin;i<knn+begin;i++)
        map[data[i].getClass()]++;

    std::vector<pair> vec;

    std::copy(map.begin(),
              map.end(),
              std::back_inserter<std::vector<pair>>(vec));

    std::sort(vec.begin(),
              vec.end(),
              [](const auto& _1, const auto& _2) {return _1.second > _2.second;}
    );

    return vec;
}

void ai::setNodesColor(std::vector<Node> &dataBase)
{

        for (Node &node: dataBase) {
            if(node.getClass().compare("UNDEFIEND"))
            {
                node.getClass().compare("Iris-versicolor") == 0 ?
                node.setColor(sf::Color::Blue) :
                node.getClass().compare("Iris-setosa") == 0 ?
                node.setColor(sf::Color::Red) :
                node.setColor(sf::Color::Green);
            }

        }

}

std::vector<Node> ai::tokenize(std::string s,Textbox& input, std::size_t size, std::string del = " ")
{

    size_t start;
    size_t end = 0;
    std::vector<double> toAdd;

    try {
        while ((start = s.find_first_not_of(del, end)) != std::string::npos)
        {
            end = s.find(del, start);
            toAdd.push_back(std::stod(s.substr(start, end - start)));

        }
        std::vector<Node> res;
        res.emplace_back(Node(toAdd, "UNDERFINED", size));
        if(toAdd.size()<size-1)
        {
            input.textbox.setString("Vector is too small");
            return {};
        }
        else if(toAdd.size()>size-1)
        {
            input.textbox.setString("Vector is too big");
            return {};
        }
        return res;
    }
    catch (std::exception& e)
    {
        input.textbox.setString("Not a vector");
        return std::vector<Node>();
    }
}

void ai::drawPoints(sf::RenderWindow& rn,sf::Text header, std::vector<Node>& data, sf::CircleShape& point, int& level, std::vector<std::pair<std::string,std::pair<int,int>>> axes,short lastPage)
{
    if(level >= lastPage)
        level = 0;
    else if(level < 0)
        level = ai::comb(data.at(0).getSize()-1,2) -1;
    if(ai::comb(data.at(0).getSize()-1,2) -1 == -1)
        level = 0;
    for (Node &node: data)
    {
        point.setPosition(
                {static_cast<float>((node.at(axes.at(level).second.first))*100), static_cast<float>((node.at(axes.at(level).second.second)) * 100 )}
        );
        point.setFillColor(node.getColor());
        rn.draw(point);

    }
    header.setString(axes.at(level).first);
    rn.draw(header);
}

std::vector<std::pair<std::string,std::pair<int,int>>> ai::getAxes()
{
    std::vector<std::pair<std::string,std::pair<int,int>>>axes;
    axes.emplace_back("X & Y",std::make_pair(0,1));

    axes.emplace_back("X & Z",std::make_pair(0,2));
    axes.emplace_back("Y & Z",std::make_pair(1,2));

    axes.emplace_back("X & W",std::make_pair(0,3));
    axes.emplace_back("Y & W",std::make_pair(1,3));
    axes.emplace_back("Z & W",std::make_pair(2,3));

    axes.emplace_back("X & V",std::make_pair(0,4));
    axes.emplace_back("Y & V",std::make_pair(1,4));
    axes.emplace_back("Z & V",std::make_pair(2,4));
    axes.emplace_back("W & V",std::make_pair(3,4));

    axes.emplace_back("X & U",std::make_pair(0,5));
    axes.emplace_back("Y & U",std::make_pair(1,5));
    axes.emplace_back("Z & U",std::make_pair(2,5));
    axes.emplace_back("W & U",std::make_pair(3,5));
    axes.emplace_back("V & U",std::make_pair(4,5));

    axes.emplace_back("X & R",std::make_pair(0,6));
    axes.emplace_back("Y & R",std::make_pair(1,6));
    axes.emplace_back("Z & R",std::make_pair(2,6));
    axes.emplace_back("W & R",std::make_pair(3,6));
    axes.emplace_back("V & R",std::make_pair(4,6));
    axes.emplace_back("U & R",std::make_pair(5,6));

    axes.emplace_back("X & S",std::make_pair(0,7));
    axes.emplace_back("Y & S",std::make_pair(1,7));
    axes.emplace_back("Z & S",std::make_pair(2,7));
    axes.emplace_back("W & S",std::make_pair(3,7));
    axes.emplace_back("V & S",std::make_pair(4,7));
    axes.emplace_back("U & S",std::make_pair(5,7));
    axes.emplace_back("R & S",std::make_pair(6,7));

    axes.emplace_back("X & T",std::make_pair(0,8));
    axes.emplace_back("Y & T",std::make_pair(1,8));
    axes.emplace_back("Z & T",std::make_pair(2,8));
    axes.emplace_back("W & T",std::make_pair(3,8));
    axes.emplace_back("V & T",std::make_pair(4,8));
    axes.emplace_back("U & T",std::make_pair(5,8));
    axes.emplace_back("R & T",std::make_pair(6,8));
    axes.emplace_back("S & T",std::make_pair(7,8));

    return axes;
}

int ai::factorial(int n)
{
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}

int ai::comb(int N, int K)
{
    return ai::factorial(N) / (ai::factorial(K) * ai::factorial(N - K));
}
