#pragma once

#include <complex>
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
            data.emplace_back(Node(toAdd,"unknown",row.size()));
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

void ai::findClass(std::vector<Node>& data,Node& node, int knn, int begin)
{
    if(knn+begin > data.size())
        knn = data.size();
    std::vector<pair> vec = ai::makeVector(data,begin,knn);
    if(vec.size()==1)
    {
        ai::printVec(vec);
        node.setClass(vec.at(0).first);
        node.printNode();
        std::cout<<"Accuracy 100%"<<'\n'<<'\n';
        data.push_back(node);
    }
    else if( vec.at(0).second == vec.at(1).second && (begin < data.size() && knn < data.size()))
    {
        ai::findClass(data,node,knn,begin+knn);
    }
    else if( vec.at(0).second > vec.at(1).second)
    {
        printVec(vec);
        node.setClass(vec.at(0).first);
        int sum = 0;
        std::for_each(vec.begin(),vec.end(),[&sum](pair& p){sum = sum + p.second;});
        node.printNode();
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
        std::cout<<"Accuracy: " << static_cast<int>((vec.at(0).second * 100)/sum)<<'%'<<'\n'<<'\n';
        data.push_back(node);
    }
}

void ai::knnAlgorithm(std::vector<Node>& dataBase, std::vector<Node>& testDataBase, int k)
{

    for(Node& test_n : testDataBase)
    {
        for (Node &data_n: dataBase)
            countDistance(test_n, data_n);

        std::sort(dataBase.begin(),
                   dataBase.end(),
                   [](const auto& _1, const auto& _2) { return _1.distance < _2.distance; });

        ai::findClass(dataBase, test_n, k);
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
    for(Node& node : dataBase){
        if(node.getClass().compare("UNDEFIEND")!= 0)
        {
            node.getClass().compare("Iris-versicolor")==0 ?
                    node.color = sf::Color::Blue :
            node.getClass().compare("Iris-setosa")==0 ?
                    node.color = sf::Color::Red :
                    node.color = sf::Color::Green;
        }
    }
}
