#include <iostream>
#include <SFML/Graphics.hpp>
#include<cstdlib>
#include <random>
#include "object.cpp"
#include "player.cpp"
#include "text.cpp"
using namespace std;

class Ball: public objects{

private:
    
    float radius;
    sf::CircleShape circle;
    sf::Vector2u WindowSize;
    int random;
    bool wasOut;




public:
    Ball(float radius, sf::RenderWindow &window){
        this->radius = radius;
        circle.setRadius(radius);
        circle.setPosition(512, 512);
        circle.setOrigin(radius, radius);
        isFixed = false;
        this->window=&window;
        velocity=sf::Vector2f(-6, 6);
        size = sf::Vector2f(2*radius, 2*radius);
        type = "ball";
        WindowSize = window.getSize();
        random = generateRandomNumber(1, 4);
        wasOut = true;
        

    }

    void Move(){
        circle.move(velocity);
    }

    void update(){
        int arr[4][2] = {{1,1}, {1,-1}, {-1, 1}, {-1, -1}};
        if(wasOut == true){
            wasOut = false;
            

            int random = generateRandomNumber(0, 3);
            int a[2] = {arr[random][0], arr[random][1]};
            velocity.x = a[0]*abs(velocity.x);
            velocity.y = a[1]*abs(velocity.y);
        }
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

                if(position.x > position_obj.x && (position.y < position_obj.y+size_obj.y/2 && position.y > position_obj.y - size_obj.y/2)){
                    circle.setPosition(position_obj.x + size_obj.x/2 + size.x/2 + 1, position.y);
                    velocity.x = -1*velocity.x;
                }
                else if(position.x < position_obj.x && (position.y < position_obj.y+size_obj.y/2 && position.y > position_obj.y - size_obj.y/2)){
                    circle.setPosition( position_obj.x - size_obj.x/2 - size.x/2 - 1 , position.y);
                    velocity.x = -1*velocity.x;
                }
                else if(position.y > position_obj.y){
                    circle.setPosition(position.x , position_obj.y + size_obj.y/2 + size.y/2 + 1);
                    velocity.y = -1*velocity.y;
                }
                else{
                    circle.setPosition(position.x, position_obj.y - size_obj.y/2 - size.y/2 -1 );
                    velocity.y = -1*velocity.y;
                }
            }
    }


    void outOfBounds(Player &p1, Player &p2, text &txt){
        
        if(position.x < 0){
            p2.incrementPoints();
            circle.setPosition(WindowSize.x/2, WindowSize.y/2);
            cout<<"P1 = "<<p1.points<<" P2 = "<<p2.points<<endl;
            wasOut = true;
            txt._setText(p1.points, p2.points);
        }
        else if(position.x > WindowSize.x){
            p1.incrementPoints();
            circle.setPosition(WindowSize.x/2, WindowSize.y/2);
            cout<<"P1 = "<<p1.points<<" P2 = "<<p2.points<<endl;
            wasOut = true;
            txt._setText(p1.points, p2.points);
        }

        int p1_points = p1.points;
        int p2_points = p2.points;

       // _setText(p1_points, p2_points);
        
    }



    int generateRandomNumber(int min, int max) {
  // Generate a random number between min and max
  int randomNumber = rand() % (max - min + 1) + min;

  // Return the random number
  return randomNumber;
}





    

};




