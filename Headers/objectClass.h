#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<string>

class Object{
public:
    bool isFixed;
    float Mass;
    sf::Vector2f Position;
    sf::Vector2f Velocity;   
};

class Player1: public Object{
public:
    sf::RectangleShape *player;
    sf::Clock clk;
    float time;
    
public:    
    Player1(sf::RectangleShape *player, sf::Window &window){
        this->player=player;
        isFixed=false;
        player->setSize(sf::Vector2f(50, 200));
        player->setOrigin(sf::Vector2f(25, 100));
        player->setPosition(sf::Vector2f(30,window.getSize().y/2));
        time=0;
    }

    void update(){
        time+=clk.restart().asSeconds();

        if(time>0.003){
            Move();
            time=0;
        }
    }

    void Move(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            player->move(0.0f, -2.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            player->move(0.0f, 2.0f);
        }
    }


    sf::Vector2f getPosition(){
       return player->getPosition();
    }


};


class Player2: public Object{
public:
    sf::RectangleShape *player;
    sf::Clock clk;
    float time;
public:    
    Player2(sf::RectangleShape *player, sf::Window &window){
        this->player=player;
        isFixed=false;
        player->setSize(sf::Vector2f(50, 200));
        player->setOrigin(sf::Vector2f(25, 100));
        player->setPosition(sf::Vector2f(window.getSize().x-30,window.getSize().y/2));
        time=0;
    }

    void update(){
        time+=clk.restart().asSeconds();

        if(time>0.003){
            Move();
            time=0;
        }
    }

    

    void Move(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            player->move(0.0f, -2.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            player->move(0.0f, 2.0f);
        }
    }

    
};


class Ball: public Object{
public:

    Ball(sf::CircleShape *ball, sf::RenderWindow &window, sf::RectangleShape *pl1, sf::RectangleShape *pl2, sf::RectangleShape *plat1, sf::RectangleShape *plat2){
        this->ball=ball;
        ball->setRadius(25);
        ball->setOrigin(sf::Vector2f(25,25));
        ball->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
        this->plat1=plat1;
        this->plat2=plat2;
        atValidLocation=true;
        Velocity = sf::Vector2f(4,4);
        this->pl1=pl1;
        this->pl2=pl2;
        sizex=window.getSize().x;
        sizey=window.getSize().y;
        time=0;
        p1c=0;
        p2c=0;
    }

    int Collision(){
        float distance1, distance2;
        sf::Vector2f deltaPo;
        float ballSize;
        sf::Vector2f ballPo, pl1Po, pl2Po, plSize;

        ballPo=ball->getPosition();
        pl1Po=pl1->getPosition();
        pl2Po=pl2->getPosition();
        ballSize=ball->getRadius();
        plSize=pl1->getSize();
        
        //With Player1
        deltaPo = sf::Vector2f(abs(ball->getPosition().x-pl1->getPosition().x),abs(ball->getPosition().y-pl1->getPosition().y));
        distance1 = deltaPo.x - ball->getRadius() - pl1->getSize().x/2;
        distance2 = deltaPo.y - ball->getRadius() - pl1->getSize().y/2;
        if(distance1<0 && distance2 < 0){


            if(abs(ballPo.y-pl1Po.y)<plSize.y/2){
                ball->move(-distance1,0);
                Velocity.x=-Velocity.x;
            }
            else{
                if(ballPo.y-pl1Po.y<0){
                    ball->setPosition(ballPo.x, pl1Po.y-plSize.y/2-ballSize-1);
                    Velocity.y=-abs(Velocity.y);
                    std::cout<<"here"<<std::endl;
                }
                else{
                    ball->setPosition(ballPo.x,pl1Po.y+plSize.y/2+ballSize);
                    Velocity.y=abs(Velocity.y);
                    std::cout<<"HERE"<<std::endl;
                }
            }
        }
        

        //With Player2
        deltaPo = sf::Vector2f(abs(ball->getPosition().x-pl2->getPosition().x),abs(ball->getPosition().y-pl2->getPosition().y));
        distance1 = deltaPo.x - ball->getRadius() - pl2->getSize().x/2;
        distance2 = deltaPo.y - ball->getRadius() - pl2->getSize().y/2;

        if(distance1<0 && distance2 < 0){
            if(abs(ballPo.y-pl2Po.y)<plSize.y/2){
                ball->move(distance1,0);
                Velocity.x=-Velocity.x;
            }
            else{
                if(ballPo.y-pl2Po.y<0){
                    ball->setPosition(ballPo.x, pl2Po.y-plSize.y/2-ballSize-1);
                    Velocity.y=-abs(Velocity.y);
                    std::cout<<"here"<<std::endl;
                }
                else{
                    ball->setPosition(ballPo.x, pl2Po.y+plSize.y/2+ballSize+1);
                    Velocity.y=abs(Velocity.y);
                    std::cout<<"HERE"<<std::endl;
                }
            }
        }
        

        //With Platform 1
        deltaPo = sf::Vector2f(abs(ball->getPosition().x-plat1->getPosition().x),abs(ball->getPosition().y-plat1->getPosition().y));
        distance1 = deltaPo.x - ball->getRadius() - plat1->getSize().x/2;
        distance2 = deltaPo.y - ball->getRadius() - plat1->getSize().y/2;

        if(distance1<0 && distance2 < 0){
            
            ball->move(0,-distance2-1);
            Velocity.y= -Velocity.y;
            
        }
        

        //With Platform 2
        deltaPo = sf::Vector2f(abs(ball->getPosition().x-plat2->getPosition().x),abs(ball->getPosition().y-plat2->getPosition().y));
        distance1 = deltaPo.x - ball->getRadius() - plat2->getSize().x/2;
        distance2 = deltaPo.y - ball->getRadius() - plat2->getSize().y/2;

        if(distance1<0 && distance2 < 0){
            ball->move(0,distance2+1);
            Velocity.y= -Velocity.y;
            }
        
        

    return 0;

    }

    void checkOutofBounds(sf::Text *text){
        
        if(ball->getPosition().x<0 || ball->getPosition().x>sizex){

            if(ball->getPosition().x<0){
                p2c++;
            }
            else{
                p1c++;
            }
            text->setString(std::to_string(p1c) + " : " + std::to_string(p2c));

            ball->setPosition(sf::Vector2f(sizex/2, sizey/2));
            Velocity.x=-Velocity.x;
            Velocity.y=-Velocity.y;
        }
    }

    

    void Move(){
        time += clk.restart().asSeconds();
        //std::cout<<time<<std::endl;
        if(time>=0.005)
           {ball->move(Velocity);
           time=0;
           }

       // ball->move(Velocity);
    }

public:
    sf::RectangleShape *pl1, *pl2;
    sf::CircleShape *ball;
    bool atValidLocation;
    sf::Vector2f Velocity;
    sf::Vector2f Position;
    sf::RectangleShape *plat1, *plat2;
    float sizex, sizey;
    sf::Clock clk;
    float time;
    bool colliding;
    int p1c;
    int p2c;

};

class Platform: public Object{
public:
    Platform(sf::RenderWindow *window, sf::Vector2f Position, sf::RectangleShape *player1, sf::RectangleShape *player2){
        this->window = window;
        this->player1=player1;
        this->player2=player2;
        rect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y/30));
        rect.setOrigin(sf::Vector2f(rect.getSize().x/2, rect.getSize().y/2));
        rect.setPosition(Position);
    }

    void Draw(){
        window->draw(rect);
    }

    sf::RectangleShape *ret(){
        return &rect;
    }

    void collisionCheck(){
        //for player1
        float check=rect.getPosition().y- player1->getPosition().y;
        float delta = abs(check);
        float distance= delta - rect.getSize().y/2 - player1->getSize().y/2;
        if (distance<0){
            if(check<0){
            player1->setPosition(sf::Vector2f(player1->getPosition().x,rect.getSize().y + player1->getSize().y/2));
        }
            if(check>0){
                player1->setPosition(sf::Vector2f(player1->getPosition().x,rect.getPosition().y-rect.getSize().y/2 - player1->getSize().y/2));
            }
        }
    
        //for player2
        check=rect.getPosition().y- player2->getPosition().y;
        delta = abs(check);
        distance= delta - rect.getSize().y/2 - player2->getSize().y/2;
        if (distance<0){
            if(check<0){
            player2->setPosition(sf::Vector2f(player2->getPosition().x,rect.getSize().y + player2->getSize().y/2));
        }
            if(check>0){
                player2->setPosition(sf::Vector2f(player2->getPosition().x,rect.getPosition().y-rect.getSize().y/2 - player2->getSize().y/2));
            }
        }
        
    }

public:
    sf::RectangleShape *player1, *player2;
    sf::RectangleShape rect;
    sf::RenderWindow *window;
};
