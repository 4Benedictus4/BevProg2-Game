#include "Player.h"

Player::Player(const int num) : Number(num) {
    if(Number==1){
        C.push_back(255);
        C.push_back(0);
        C.push_back(0);
        IsAc=true;
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

void Player::Log(){
    std::string gold;
    std::stringstream ss;
    ss<<Gold;
    ss>>gold;
    genv::gout<<genv::color(white)<<genv::move_to(XX-290, YY-45)<<genv::text("Gold: ")<<genv::text(gold);
}
