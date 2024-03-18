#include "object.cpp"
#include<SFML/Graphics.hpp>

class Player: public objects{
    private:
        sf::Vector2f size;
        sf::RectangleShape player;

    
    public:
        Player(float x, float y, sf::RenderWindow &window){
            size = sf::Vector2f(x , y);
            player.setSize(size);
            velocity = sf::Vector2f(0, 0);
            position = sf::Vector2f(0,0);
            isFixed = true;
            this->window=&window;
            player.setOrigin(x/2, y/2);
        }

        void setPosition_(float x, float y){
            player.setPosition(x, y);
        }

        void Move(){
            player.move(velocity);
        }

        void Draw(){
            window->draw(player);
        }
};