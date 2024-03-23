#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.cpp"
#include "player.cpp"
using namespace std;

class Ball: public objects{

private:
    
    float radius;
    sf::CircleShape circle;
    sf::Vector2u WindowSize;


public:
    Ball(float radius, sf::RenderWindow &window){
        this->radius = radius;
        circle.setRadius(radius);
        circle.setPosition(512, 512);
        circle.setOrigin(radius, radius);
        isFixed = false;
        this->window=&window;
        velocity=sf::Vector2f(2,-2);
        size = sf::Vector2f(2*radius, 2*radius);
        type = "ball";
        WindowSize = window.getSize();
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
    
    string getType(){
        return "ball";
    }

    sf::Vector2f getPosition_(){
        return circle.getPosition();
    }

    void collisionHandler(objects* obj){
        float vel_x = velocity.x;
        float vel_y = velocity.y;


        if(obj->getType() == "platform"){
                sf::Vector2f position_obj = obj->getPosition_();
                sf::Vector2f size_obj = obj->getSize_();

                if(position.y > position_obj.y){
                    circle.setPosition(position.x, position_obj.y+ size_obj.y/2 + size.y/2 +1);
                    velocity.y = -1*velocity.y;
                }
                else{
                    circle.setPosition(position.x, position_obj.y - size_obj.y/2 - size.y/2 - 1);
                    velocity.y = -1*velocity.y;
                }
            }

        if(obj->getType() == "player"){
                sf::Vector2f position_obj = obj->getPosition_();
                sf::Vector2f size_obj = obj->getSize_();

                if(position.x > position_obj.x){
                    circle.setPosition(position_obj.x + size_obj.x/2 + size.x/2 + 1, position.y);
                    velocity.x = -1*velocity.x;
                }
                else{
                    circle.setPosition( position_obj.x - size_obj.x/2 - size.x/2 - 1 , position.y);
                    velocity.x = -1*velocity.x;
                }
            }
    }


    void outOfBounds(Player &p1, Player &p2){
        
        if(position.x < 0){
            p2.incrementPoints();
            circle.setPosition(WindowSize.x/2, WindowSize.y/2);
            cout<<"P1 = "<<p1.points<<" P2 = "<<p2.points<<endl;
        }
        else if(position.x > WindowSize.x){
            p1.incrementPoints();
            circle.setPosition(WindowSize.x/2, WindowSize.y/2);
            cout<<"P1 = "<<p1.points<<" P2 = "<<p2.points<<endl;
        }

        
    }

    

};




