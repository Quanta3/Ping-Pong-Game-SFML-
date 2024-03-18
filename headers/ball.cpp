#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.cpp"
using namespace std;

class Ball: public objects{

private:
    
    float radius;
    sf::CircleShape circle;



public:
    Ball(float radius, sf::RenderWindow &window){
        this->radius = radius;
        circle.setRadius(radius);
        circle.setPosition(512, 512);
        circle.setOrigin(radius, radius);
        isFixed = false;
        this->window=&window;
    }

    void Move(){
        circle.move(velocity);
    }

    void update(){
        Move();
        position = circle.getPosition();
    }

    void Draw(){
        window->draw(circle);
    }
    

};




