#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
#pragma once

class objects{
    protected:
    sf::RenderWindow *window;
    bool isSolid;
    bool isFixed;
    sf::Vector2f velocity;
    sf::Vector2f position;


    public:
        sf::Vector2f getPosition_(){
            return position;
        }

        virtual void Draw(){
            cout<<"incorrect";
        };

       
};

