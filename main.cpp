#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/System.hpp>
#include "Headers/objectClass.h"

static const float VIEW_HEIGHT  = 950;

void ResizeView(sf::RenderWindow &window, sf::View &view){
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(aspectRatio*VIEW_HEIGHT+100, VIEW_HEIGHT);

}

int main(){
    sf::RenderWindow window(sf::VideoMode(950, 950), "Ping-Pong", sf::Style::Close|sf::Style::Titlebar);

    sf::View view(sf::Vector2f(475, 275),sf::Vector2f(950, 950));

    sf::Font font;
    font.loadFromFile("ARIAL.ttf");
    sf::Text text("0:0", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(475,50);
    text.setOutlineThickness(2);
    text.setOrigin(15,15);

    


    sf::RectangleShape player1;
    sf::RectangleShape player2;
    sf::CircleShape ball;
    Player1 pl1(&player1, window);
    Player2 pl2(&player2, window); 
    Platform p1(&window, sf::Vector2f(window.getSize().x/2, window.getSize().y/60), &player1, &player2);
    Platform p2(&window, sf::Vector2f(window.getSize().x/2, window.getSize().y-window.getSize().y/60), &player1, &player2);
    Ball bl(&ball, window, &player1, &player2, p1.ret(), p2.ret());
    bool paused=false;
    float time=0;
    sf::Clock clk;
    clk.restart().asSeconds();
    
    while(window.isOpen()){
        sf::Event ev;

        while(window.pollEvent(ev)){
            if(ev.type==ev.Closed){
                window.close();
            }
            if(ev.type==sf::Event::Resized){
                ResizeView(window, view);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            time=clk.restart().asSeconds();
            std::cout<<"here"<<std::endl;
            if(time>=0.1){
                paused?paused=false:paused=true;
            } 
        }
        if(paused){
            continue;
        }

        pl1.update();
        pl2.update();
       
        bl.Move();
        
        bl.Collision();
        bl.checkOutofBounds(&text);
        p1.collisionCheck();
        p2.collisionCheck();
       
        window.clear();
        view.setCenter(475, 475);
        window.setView(view);
        window.draw(text);
        window.draw(ball);
        window.draw(player1);
        window.draw(player2);
        p1.Draw();
        p2.Draw();
        window.display();
    }
}