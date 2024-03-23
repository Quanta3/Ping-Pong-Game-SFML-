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
    sf::Vector2f size;
    string type;


    public:
        sf::Vector2f getPosition_(){
            return position;
        }

        sf::Vector2f getSize_(){
            return size;
        }

        virtual void Draw(){
            cout<<"incorrect";
        };

        virtual void collisionHandler(objects* obj){
           // cout<<"Incorrect";
        }

        string getType(){
            return type;
        }
       
};

