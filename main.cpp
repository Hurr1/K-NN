#include "CSVRow.h"
#include <iostream>
#include <map>
#include "Node.h"
#include <cmath>
#define ARGS_NUMBER argc-1


std::istream& operator>>(std::istream& str, CSVRow& data);

std::vector<Node> createDB(std::istream& str);
std::vector<Node> createTestDB(std::ifstream& str);
void countDistance(Node& first, Node& second);

int main(int argc, char* argv[])
{
    if(ARGS_NUMBER==3)
    {
        std::ifstream trainSet(argv[2]),
                      testSet(argv[3]);
        std::vector<Node>dataBase;
        std::vector<Node>testDataBase;

        if(trainSet && testSet)
        {

            dataBase = ::createDB(trainSet);
            testDataBase = ::createTestDB(testSet);

            for(Node n : dataBase)
                n.printNode();
            std::cout<<"-----------------------------"<<'\n'<<'\n';
            testDataBase.at(0).printNode();
            countDistance(testDataBase.at(0),dataBase.at(0));
            std::cout<<dataBase.at(0).distance;



        }else{
            trainSet ? std::cout<<"There no file with name: "<<argv[3]<<'\n' : std::cout<<"There no file with name: " << argv[2]<<'\n';
            return EXIT_SUCCESS;
        }
    }else{
        std::cout<<"Invalid number of arguments"<<'\n';
    }

    return EXIT_SUCCESS;
}

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

std::vector<Node> createDB(std::istream& str)
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

std::vector<Node> createTestDB(std::ifstream& str)
{
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
}

void countDistance(Node& first, Node& second)
{
    double distance = 0;
    for(int i =0;i< first.getSize()-1;i++)
        distance = distance +  std::pow(first.at(i)-second.at(i),2);
    second.distance = distance;
}



