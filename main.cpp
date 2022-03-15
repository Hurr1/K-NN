#include "CSVRow.h"
#include <iostream>
#include <map>
#define ARGS_NUMBER argc-1

std::istream& operator>>(std::istream& str, CSVRow& data);

int main(int argc, char* argv[])
{
    dsgsdgsd
    if(ARGS_NUMBER==3)
    {
        std::ifstream trainSet(argv[2]),
                      testSet(argv[3]);

        if(trainSet && testSet)
        {
            CSVRow row;
            while(trainSet >> row)
            {
                for(int i = 0; i< row.size();i++)
                    std::cout<<"["<<row[i]<<']';
                std::cout<<'\n';
            }
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
