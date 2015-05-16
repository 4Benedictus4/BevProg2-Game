#include "Hill.h"

void Hill::draw(){
    gout<<move_to(X,Y)<<color(black)<<box(W,H)<<move_to(X+1,Y+1)<<color(150, 100, 0)<<box(W-2,H-2);
}

void Hill::Set(event ev){

}

std::map<std::string, int> Hill::get_mods(){
    std::map<std::string, int> m;
    m["dm"]=def_mod;
    m["am"]=atk_mod;
    m["rm"]=range_mod;
    return m;
}

void Hill::Log(){
    Landscape::Log();
    std::string dm, am, rm;
    std::stringstream ss;
    ss<<def_mod<<" "<<atk_mod<<" "<<range_mod;
    ss>>dm>>am>>rm;
    gout<<color(white)<<move_to(150,YY-85)<<text("Hill")<<move_to(150,YY-65)<<text(am)<<move_to(150,YY-45)<<text(dm)<<move_to(150, YY-25)<<text(rm);
}
