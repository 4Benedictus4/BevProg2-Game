#include "Forest.h"

void Forest::draw(){
    gout<<move_to(X,Y)<<color(black)<<box(W,H)<<move_to(X+1,Y+1)<<color(0, 100, 0)<<box(W-2,H-2);
}

void Forest::Set(event ev){

}

std::map<std::string, int> Forest::get_mods(){
    std::map<std::string, int> m;
    m["dm"]=def_mod;
    m["am"]=atk_mod;
    return m;
}

void Forest::Log(){
    Landscape::Log();
    std::string dm, am;
    std::stringstream ss;
    ss<<def_mod<<" "<<atk_mod;
    ss>>dm>>am;
    gout<<color(white)<<move_to(150,YY-80)<<text("Forest")<<move_to(150,YY-60)<<text(am)<<move_to(150,YY-40)<<text(dm);
}
