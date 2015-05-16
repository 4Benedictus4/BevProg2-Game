#include "Plain.h"

void Plain::draw(){
    gout<<move_to(X,Y)<<color(black)<<box(W,H)<<move_to(X+1,Y+1)<<color(200, 255, 50)<<box(W-2,H-2);
}

void Plain::Set(event ev){

}

std::map<std::string, int> Plain::get_mods(){
    std::map<std::string, int> m;
    m["dm"]=def_mod;
    m["am"]=atk_mod;
    return m;
}

void Plain::Log(){
    Landscape::Log();
    std::string dm, am;
    std::stringstream ss;
    ss<<def_mod<<" "<<atk_mod;
    ss>>dm>>am;
    gout<<color(white)<<move_to(150,YY-80)<<text("Plain")<<move_to(150,YY-60)<<text(am)<<move_to(150,YY-40)<<text(dm);
}
