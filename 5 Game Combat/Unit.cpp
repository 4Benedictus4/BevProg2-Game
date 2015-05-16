#include "Unit.h"

Unit::Unit(const int x, const int y, const int w, const int h, const int id, std::string type) : Controlled(x, y, w, h, id){
    if(type=="w"){
        atk=15;
        def=10;
        hp=20;
        range=1;
        movepoints=1;
        atkpoints=1;
        atk_mod=0;
        def_mod=0;
    }
    if(type=="a"){
        atk=10;
        def=5;
        hp=15;
        range=2;
        movepoints=1;
        atkpoints=1;
        atk_mod=0;
        def_mod=0;
    }
    if(type=="b"){

    }
}

void Unit::take_damage(int dmg){
    int mod=dmg-(def+def_mod);
    if(mod>0) hp-=mod;
}


void Unit::Log(){
    gout<<color(white)<<move_to(255,YY-85)<<text("Unit type: ")<<move_to(255,YY-65)<<text("Attack: ")<<move_to(255,YY-45)<<text("Defense: ")<<move_to(255, YY-25)<<text("Health: ")<<move_to(255, YY-5)<<text("Range: ");
}

void Unit::Move(int x, int y){
    if(movepoints>0){
        X=x;
        Y=y;
    }
    ///movepoints--;
    if(movepoints<=0) DeActivate();
}

void Unit::Attack(){
    if(atkpoints>0) ///atkpoints--;
    if(atkpoints<=0) DeActivate();
}

std::map<std::string, int> Unit::get_stats(){
    std::map<std::string, int> m;
    m["atk"]=atk;
    m["def"]=def;
    m["hp"]=hp;
    m["r"]=range;
    m["am"]=atk_mod;
    m["dm"]=def_mod;
    return m;
}

void Unit::mod_stats(int am, int dm){
    atk_mod=am;
    def_mod=dm;
}


