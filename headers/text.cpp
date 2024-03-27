#pragma once
#include "object.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class text: public objects{
    public:
    sf::Text txt;
    sf::Font font;

    text(){
        font.loadFromFile("ARIAL.ttf");
        txt.setString("0:0");
        txt.setPosition(512, 40);
        txt.setFont(font);
    }
    
    
    void _setText(int p1_points, int p2_points){
    string t = to_string(p1_points) + " : " + to_string(p2_points);
    txt.setString(t);
    }

    void Draw(){
        window->draw(txt);
    }

};