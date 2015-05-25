#include "Unit.h"

Unit::Unit(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type) : Controlled(x, y, w, h, id, player, type){
    Type=type;
    if(type=="w"){
        atk=16; /// +2 ???
        def=10;
        hp=20;
        range=1;
        movepoints=1;
        atkpoints=1;
        atk_mod=0;
        def_mod=0;
        range_mod=0;
        cost=40;
    }
    if(type=="a"){
        atk=14;
        def=8;
        hp=15;
        range=2;
        movepoints=1;
        atkpoints=1;
        atk_mod=0;
        def_mod=0;
        range_mod=0;
        cost=50;
    }
    if(type=="b"){

    }
}

Unit::Unit(std::string type) : Controlled(type){
    Type=type;
    if(type=="w"){
        cost=40;
    }
    if(type=="a"){
        cost=50;
    }
    if(type=="b"){

    }
}

void Unit::take_damage(int dmg){
    int mod=dmg-(def+def_mod);
    if(mod>0) hp-=mod;
}


void Unit::Log(){
    gout<<color(white)<<move_to(220,YY-85)<<text("MP: ")<<move_to(300,YY-85)<<text("AP: ")<<move_to(220,YY-65)<<text("Attack: ")<<move_to(220,YY-45)<<text("Defense: ")<<move_to(220, YY-25)<<text("Health: ")<<move_to(220, YY-5)<<text("Range: ");
}

void Unit::Move(int x, int y){
    if(movepoints>0){
        X=x;
        Y=y;
    }
    movepoints--;
    if(movepoints<=0) DeActivate();
}

void Unit::Attack(){
    if(atkpoints>0) atkpoints--;
    if(atkpoints<=0) DeActivate();
}

std::map<std::string, int> Unit::get_stats(){
    std::map<std::string, int> m;
    m["atk"]=atk+atk_mod;
    m["def"]=def+def_mod;
    m["movep"]=movepoints;
    m["hp"]=hp;
    if(Type=="a") m["r"]=range+range_mod;
    else m["r"]=range;
    return m;
}

void Unit::mod_stats(int am, int dm, int rm){
    atk_mod=am;
    def_mod=dm;
    range_mod=rm;
}


