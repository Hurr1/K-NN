#include "../Headers/CSVRow.h"
#include <iostream>
#include "../Headers/Node.h"
#include <cmath>
#include "../Headers/Algorithms.h"
#include "../Headers/Button.h"
#include <SFML/Graphics.hpp>
#define ARGS_NUMBER argc-1


int main(int argc, char* argv[])
{

    if(ARGS_NUMBER==3)
    {
        std::ifstream trainSet("Resources/" + static_cast<std::string>(argv[2])),
                      testSet("Resources/" + static_cast<std::string>(argv[3]));
        std::vector<Node>dataBase;
        std::vector<Node>testDataBase;

        if(trainSet && testSet)
        {
            int k = std::atoi((argv[1]));

            dataBase = ai::createDB(trainSet);
            testDataBase = ai::createTestDB(testSet);

            {
                k > dataBase.size() ? k = dataBase.size() : NULL;
                k > 0 ? NULL : k = 3;
            }


            {
                if (dataBase.empty() || testDataBase.empty()) {
                    if (dataBase.empty())
                        std::cout << "TrainingSet.cvs is empty." << '\n';
                    if (testDataBase.empty())
                        std::cout << "TestSet.cvs is empty." << '\n';

                    std::cout << "Programs ends with exit code 0" << '\n';
                    exit(1);
                }
                if (dataBase.at(0).getSize() == 1 || dataBase.at(0).getSize() == 0) {
                    std::cout << "Vector is empty." << '\n' << "Programs ends with exit code 0" << '\n';
                    exit(1);
                }
            }

            ai::knnAlgorithm(dataBase,testDataBase,k);
            ai::setNodesColor(dataBase);

            sf::RenderWindow rn (sf::VideoMode(960,540),"KNN simulation", sf::Style::Close);

            sf::Font font;
            font.loadFromFile("Resources/arial.ttf");

            sf::Texture backGround;
            backGround.loadFromFile("Resources/map.png");
            sf::Sprite bgSprite(backGround);


            sf::Text header;
            header.setFont(font);
            header.setString("X & Y");
            header.setCharacterSize(40);
            header.setFillColor(sf::Color::White);
            header.setPosition(430, 30);

            sf::CircleShape point(5);

            Textbox InputBox(50, sf::Color::White, true);
            InputBox.setPosition({0, 480 });
            InputBox.setLimit(true, 16);
            InputBox.setFont(font);

            Button vectorButton("Enter", {100, 50 }, 20, sf::Color::White, sf::Color::Black);
            vectorButton.setFont(font);
            vectorButton.setPosition({425, 490 });

            std::vector<Node> input;
            int axis = 0;
            std::vector<std::pair<std::string,std::pair<int,int>>> axes = ai::getAxes();
            short lastPage = ai::comb(dataBase.at(0).getSize()-1,2);
            while(rn.isOpen())
            {

                rn.clear();

                rn.draw(bgSprite);
                ai::drawPoints(rn,header,dataBase,point,axis,axes,lastPage);
                InputBox.drawTo(rn);
                vectorButton.drawTo(rn);

                sf::Event evnt{};

                while(rn.pollEvent(evnt))
                {
                    switch(evnt.type)
                    {
                        case sf::Event::Closed:
                            rn.close();
                            break;
                        case sf::Event::TextEntered:
                            InputBox.typedOn(evnt);
                        case sf::Event::MouseMoved:
                            if (vectorButton.isMouseOver(rn)) {
                                vectorButton.setBackColor(sf::Color::Green);
                            }
                            else {
                                vectorButton.setBackColor(sf::Color::White);
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if (vectorButton.isMouseOver(rn))
                            {
                                input = ai::tokenize(InputBox.getText(), InputBox, dataBase.at(0).getSize()," ");
                                if(!input.empty())
                                {
                                    ai::knnAlgorithm(dataBase, input, k);
                                    ai::setNodesColor(dataBase);

                                    InputBox.textbox.setString(
                                            dataBase.at(dataBase.size() - 1).getClass() + " " +
                                            std::to_string((dataBase.at(dataBase.size() - 1).getPercent())) + "%"
                                    );
                                    input.clear();
                                }
                            }
                            break;
                        case sf::Event::KeyPressed:
                            if(evnt.key.code == sf::Keyboard::Right)
                                axis++;
                            else if(evnt.key.code == sf::Keyboard::Left)
                                axis--;
                            break;
                    }
                }
                rn.display();
            }

        }else{
            trainSet ? std::cout<<"There no file with name: "<<argv[3]<<'\n' : std::cout<<"There no file with name: " << argv[2]<<'\n';
            return EXIT_FAILURE;
        }
    }else{
        std::cout<<"Invalid number of arguments"<<'\n';
    }
    return EXIT_SUCCESS;
}






