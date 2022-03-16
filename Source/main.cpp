#include "../Headers/CSVRow.h"
#include <iostream>
#include "../Headers/Node.h"
#include <cmath>
#include "../Headers/Algorithms.h"
#define ARGS_NUMBER argc-1


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

            dataBase = ai::createDB(trainSet);
            testDataBase = ai::createTestDB(testSet);

            ai::knnAlgorithm(dataBase,testDataBase,std::atoi(argv[1]));

        }else{
            trainSet ? std::cout<<"There no file with name: "<<argv[3]<<'\n' : std::cout<<"There no file with name: " << argv[2]<<'\n';
            return EXIT_FAILURE;
        }
    }else{
        std::cout<<"Invalid number of arguments"<<'\n';
    }
    return EXIT_SUCCESS;
}






