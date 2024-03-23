#include "object.cpp"
#include <SFML/Graphics.hpp>

class Platform: public objects{
    private:
        
        sf::RectangleShape platform;

    
    public:
        Platform(float x, float y, sf::RenderWindow &window){
            size = sf::Vector2f(x , y);
            platform.setSize(size);
            platform.setOrigin(x/2, y/2);
            velocity = sf::Vector2f(0, 0);
            position = sf::Vector2f(0,0);
            isFixed = true;
            this->window = &window;
            type = "platform";
        }

        void setPosition_(float x, float y){
            platform.setPosition(x, y);
            position = sf::Vector2f(x, y);
        }

        void Draw(){
            window->draw(platform);
        }

        string getType(){
            return "platform";
        }

        void collisionHandler(){
            //cout<<"Platform Collided"<<endl;
        }
};

