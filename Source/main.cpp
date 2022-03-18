#include "../Headers/CSVRow.h"
#include <iostream>
#include "../Headers/Node.h"
#include <cmath>
#include "../Headers/Algorithms.h"
#include <SFML/Graphics.hpp>
#define ARGS_NUMBER argc-1


int main(int argc, char* argv[])
{
    if(ARGS_NUMBER==3)
    {

        std::ifstream trainSet("resourses/" + static_cast<std::string>(argv[2])),
                      testSet("resourses/" + static_cast<std::string>(argv[3]));
        std::vector<Node>dataBase;
        std::vector<Node>testDataBase;

        if(trainSet && testSet)
        {
            int k = std::atoi((argv[1]));

            dataBase = ai::createDB(trainSet);
            testDataBase = ai::createTestDB(testSet);
            {
                k > dataBase.size() ? k = dataBase.size() : k = k;
                k > 0 ? k = k : k = 3;
            }
            ai::knnAlgorithm(dataBase,testDataBase,k);
            ai::setNodesColor(dataBase);

            sf::RenderWindow rn (sf::VideoMode(960,540),"KNN simulation", sf::Style::Close);

            sf::Texture backGround;
            backGround.loadFromFile("resourses/map.png");
            sf::Sprite bgSprite(backGround);
            bool axis = true;

            sf::Font font;
            font.loadFromFile("resourses/arial.ttf");

            sf::Text text;
            text.setFont(font);
            text.setString("X & Y");
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::White);
            text.setPosition(430,30);

            sf::CircleShape point(5);
            while(rn.isOpen())
            {

                rn.clear();
                rn.draw(bgSprite);
                rn.draw(text);
                if(axis) {

                    for (const Node &node: dataBase) {
                        point.setPosition(
                                            {static_cast<float>((node.getX() * 100)-100), static_cast<float>((node.getY() * 110)-30)}
                                         );
                        point.setFillColor(node.color);
                        rn.draw(point);
                    }
                }
                else
                {
                    for (const Node &node: dataBase) {
                        point.setPosition(
                                            {static_cast<float>((node.getZ() * 100)+30), static_cast<float>((node.getW() * 110)+80)}
                                          );
                        point.setFillColor(node.color);
                        rn.draw(point);
                    }
                }

                rn.display();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                {
                    text.setString("X & Y");
                    axis = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                {
                    text.setString("Z & W");
                    axis = false;
                }
                sf::Event evnt;
                while(rn.pollEvent(evnt))
                {
                    switch(evnt.type)
                    {
                        case sf::Event::Closed:
                            rn.close();
                            break;
                    }

                }
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






