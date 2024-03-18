#include <SFML/Graphics.hpp>
#include "headers/ball.cpp"
#include "headers/platform.cpp"
#include "headers/player.cpp"
#include "headers/object.cpp"
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

    
    plt2.setPosition_(0, 1024-40);
    p1.setPosition_(35, 512);
    p2.setPosition_(1024-35, 512);

    vector<objects*> obj;
    obj.push_back(&plt1);
    obj.push_back(&plt2);
    obj.push_back(&ball);
    obj.push_back(&p1);
    obj.push_back(&p2);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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