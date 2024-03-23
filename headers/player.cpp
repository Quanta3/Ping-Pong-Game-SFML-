#pragma once
#include "object.cpp"
#include<SFML/Graphics.hpp>

class Player: public objects{
    private:
        sf::RectangleShape player;
        sf::Keyboard::Key keyUp;
        sf::Keyboard::Key keyDown;
        

    
    public:
    int points;
        Player(float x, float y, sf::RenderWindow &window){
            size = sf::Vector2f(x , y);
            player.setSize(size);
            velocity = sf::Vector2f(0, 2);
            position = sf::Vector2f(0,0);
            isFixed = true;
            this->window=&window;
            player.setOrigin(x/2, y/2);
            type = "player";
            points = 0;
        }

        void setPosition_(float x, float y){
            player.setPosition(x, y);
            position = sf::Vector2f(x, y);
        }

        void Move(){
            player.move(velocity);
        }

        void Draw(){
            window->draw(player);
        }

        string getType(){
            return "player";
        }

        void update(){
            if(sf::Keyboard::isKeyPressed(keyDown)){
                player.move(velocity);
            }
            else if(sf::Keyboard::isKeyPressed(keyUp)){
                sf::Vector2f temp;
                temp.x=velocity.x;
                temp.y=-1*velocity.y;
                player.move(temp);
            }
            position = player.getPosition();
        }

        void setKeys(sf::Keyboard::Key a, sf::Keyboard::Key b){
            keyUp = a;
            keyDown = b;
        }

        void incrementPoints(){
            points++;
        }

        void collisionHandler(objects* obj){
            //cout<<"Player Collided"<<endl;

            if(obj->getType() == "platform"){
                sf::Vector2f position_obj = obj->getPosition_();
                sf::Vector2f size_obj = obj->getSize_();

                if(position.y > position_obj.y){
                    setPosition_(position.x, position_obj.y+ size_obj.y/2 + size.y/2 +1);
                }
                else{
                    setPosition_(position.x, position_obj.y - size_obj.y/2 - size.y/2 - 1);
                }
            }
        }
};