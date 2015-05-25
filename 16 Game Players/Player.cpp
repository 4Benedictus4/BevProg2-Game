#include "Player.h"

Player::Player(const int num) : Number(num) {
    if(Number==1){
        C.push_back(255);
        C.push_back(0);
        C.push_back(0);
    }
    if(Number==2){
        C.push_back(0);
        C.push_back(0);
        C.push_back(255);
    }
    if(Number==3){
        C.push_back(0);
        C.push_back(255);
        C.push_back(0);
    }
    if(Number==4){
        C.push_back(255);
        C.push_back(255);
        C.push_back(0);
    }
}

void Player::mod_Gold(int g){
    Gold+=g;
    if(Gold<=0) Gold=0;
}
