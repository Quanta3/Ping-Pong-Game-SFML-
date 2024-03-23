#include <SFML/Graphics.hpp>
#include "headers/ball.cpp"
#include "headers/platform.cpp"
#include "headers/player.cpp"
#include "headers/object.cpp"
#include "headers/collision.cpp"
#include <Vector>

void Draw(vector<objects*> &obj);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
    Platform plt1(1024, 40, window);
    Platform plt2(1024, 40, window);
    Ball ball(25, window);
    Player p1(50, 200, window);
    Player p2(50, 200, window);

    plt1.setPosition_(512, 20);
    plt2.setPosition_(512, 1024-40);
    p1.setPosition_(35, 512);
    p1.setKeys(sf::Keyboard::W, sf::Keyboard::S);
    p2.setPosition_(1024-35, 512);
    p2.setKeys(sf::Keyboard::Up, sf::Keyboard::Down);

    

    vector<objects*> obj;
    obj.push_back(&plt1);
    obj.push_back(&plt2);
    obj.push_back(&ball);
    obj.push_back(&p1);
    obj.push_back(&p2);


    collision colObj;
    

    while (window.isOpen())
    {

        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
              {  window.close();}

              
        
        }
        
        ball.outOfBounds(p1, p2);
        p1.update();
        p2.update();
        ball.update();

        colObj.check_and_handle_Collisions(obj);
        window.clear();
        Draw(obj);
        window.display();
    }

    return 0;
}

void Draw(vector<objects*> &obj){

    for(int i =0; i<obj.size(); i++){
        obj[i]->Draw();
    }

}

void Update(vector<objects*> &obj){
    
}