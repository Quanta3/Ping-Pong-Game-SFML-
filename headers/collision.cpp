#include<vector>
#include "object.cpp";
using namespace std;

class collision{
public:
    void check_and_handle_Collisions(vector<objects*> &obj){
        for(int i = 0; i<obj.size()-1; i++){
            for(int j = i+1; j<obj.size(); j++ ){
                if(checkCol_between(obj[i], obj[j])){
                    obj[i]->collisionHandler(obj[j]);
                    obj[j]->collisionHandler(obj[i]);
                }
            }
        }
    }


    bool checkCol_between(objects* &obj1, objects* &obj2){
        

        sf::Vector2f position1 = obj1->getPosition_();
        sf::Vector2f position2 = obj2->getPosition_();
        sf::Vector2f size1 = obj1->getSize_();
        sf::Vector2f size2 = obj2->getSize_();

        float distance_x;
        float distance_y;
        if(position1.x < position2.x){
            distance_x = (position2.x - size2.x/2) - (position1.x + size1.x/2);
        }
        else{
            distance_x = (position1.x - size1.x/2) - (position2.x + size2.x/2);
        }


        if(position1.y < position2.y){
            distance_y = (position2.y - size2.y/2) - (position1.y + size1.y/2);
        }
        else{
            distance_y = (position1.y - size1.y/2) - (position2.y + size2.y/2);
        }

        
        
        if(distance_x<=0 && distance_y<=0){
            return true;
        }


        return false;

        
    }

    
};