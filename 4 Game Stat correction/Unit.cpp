#include "Unit.h"

Unit::Unit(const int x, const int y, const int w, const int h, const int id, std::string type) : Controlled(x, y, w, h, id){
    if(type=="w"){
        atk=15;
        def=10;
        hp=20;
        range=1;
        movepoints=1;
        atk_mod=0;
        def_mod=0;
    }
    if(type=="a"){

    }
    if(type=="b"){

    }
}

void Unit::take_damage(int dmg){
    int mod=dmg-(def+def_mod);
    if(mod>0) hp-=mod;
}


void Unit::Log(){
    gout<<color(white)<<move_to(305,YY-80)<<text("Unit type: ")<<move_to(305,YY-60)<<text("Attack: ")<<move_to(305,YY-40)<<text("Defense: ")<<move_to(305, YY-20)<<text("Health: ");
}

void Unit::Move(int x, int y){
    if(movepoints>0){
        X=x;
        Y=y;
    }
    ///movepoints--;
    if(movepoints<=0){
        DeActivate();
    }
}

void Unit::mod_stats(int am, int dm){
    atk_mod=am;
    def_mod=dm;
}


