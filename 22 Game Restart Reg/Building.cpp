#include "Building.h"

Building::Building(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type) : Controlled(x, y, w, h, id, player){
    Type=type;
    if(type=="c"){
        atk=18;
        def=12;
        hp=30;
        range=2;
        atk_mod=0;
        def_mod=0;
        atkpoints=1;
        cost=500;
    }
    if(type=="f"){
        atk=0;
        def=16;
        hp=20;
        range=0;
        atk_mod=0;
        def_mod=0;
        atkpoints=0;
        cost=300;
    }
    if(type=="m"){
        atk=0;
        def=14;
        hp=18;
        range=0;
        atk_mod=0;
        def_mod=0;
        atkpoints=0;
        cost=200;
    }
}

void Building::Log(){
    gout<<color(white)<<move_to(420,YY-65)<<text("Attack: ")<<move_to(420,YY-45)<<text("Defense: ")<<move_to(420, YY-25)<<text("Health: ")<<move_to(420, YY-5)<<text("Range: ");
}

void Building::take_damage(int dmg){
    int mod=dmg-(def+def_mod);
    if(mod>0) hp-=mod;
}

std::map<std::string, int> Building::get_stats(){
    std::map<std::string, int> m;
    m["atk"]=atk+atk_mod;
    m["def"]=def+def_mod;
    m["hp"]=hp;
    m["r"]=range;
    return m;
}

void Building::mod_stats(int am, int dm, int rm){
    atk_mod=am;
    def_mod=dm;
}

void Building::Attack(){
    if(atkpoints>0) atkpoints--;
    if(atkpoints<=0) DeActivate();
}
