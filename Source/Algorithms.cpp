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
    while(str >> row)
    {
        std::vector<double>toAdd;
        for(int i = 0; i< row.size()-1;i++)
            toAdd.push_back(std::stod(row[i]));
        data.emplace_back(Node(toAdd,row[row.size()-1],row.size()));
        toAdd.clear();
    }
    return data;
}

std::vector<Node> ai::createTestDB(std::ifstream& str)
{
        CSVRow row;
        std::vector<Node> data;
        while(str >> row)
        {
            std::vector<double>toAdd;
            for(int i = 0; i< row.size()-1;i++)
                toAdd.push_back(std::stod(row[i]));
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
    std::unordered_map<std::string ,int>map;

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

    for (auto const &pair: vec) {
        std::cout << '{' << pair.first << "," << pair.second << '}';
    }
    std::cout<<'\n';
    if(vec.size()==1)
    {
        node.setClass(vec.at(0).first);
        node.printNode();
        std::cout<<"Accuracy 100%"<<'\n'<<'\n';
    }
    else if( vec.at(0).second == vec.at(1).second)
    {
        ai::findClass(data,node,knn,knn);
    }
    else if( vec.at(0).second > vec.at(1).second)
    {
        node.setClass(vec.at(0).first);
        int sum = 0;
        std::for_each(vec.begin(),vec.end(),[&sum](pair& p){sum = sum + p.second;});
        node.printNode();
        std::cout<<"Accuracy: " << static_cast<int>((vec.at(0).second * 100)/sum)<<'%'<<'\n'<<'\n';
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
