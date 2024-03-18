#include "object.cpp"
#include <SFML/Graphics.hpp>

class Platform: public objects{
    private:
        sf::Vector2f size;
        sf::RectangleShape platform;

    
    public:
        Platform(float x, float y, sf::RenderWindow &window){
            size = sf::Vector2f(x , y);
            platform.setSize(size);
            velocity = sf::Vector2f(0, 0);
            position = sf::Vector2f(0,0);
            isFixed = true;
            this->window = &window;
        }

        void setPosition_(float x, float y){
            platform.setPosition(x, y);
        }

        void Draw(){
            window->draw(platform);
        }
};

