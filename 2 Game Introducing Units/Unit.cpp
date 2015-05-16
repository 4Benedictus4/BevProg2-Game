#include "Unit.h"

Unit::Unit(const int x, const int y, const int w, const int h, const int id, std::string type) : Controlled(x,y,w,h,id) {
    atk_mod=0;
    def_mod=0;
    if(type=="w"){
        atk=15;
        def=10;
        hp=20;
    }


}


void Unit::Log(){
    gout<<color(white)<<move_to(255,YY-80)<<text("Unit type: ")<<move_to(255,YY-60)<<text("Attack: ")<<move_to(255,YY-40)<<text("Defense: ")<<move_to(255, YY-20)<<text("Health: ");
    std::string d, a, h, dm, am;
    std::stringstream ss;
    ss<<def<<" "<<atk<<" "<<hp<<" "<<def_mod<<" "<<atk_mod;
    ss>>d>>a>>h>>dm>>am;
    gout<<color(white)<<move_to(355,YY-80)<<text("Warrior")<<move_to(355,YY-60)<<text(a)<<text(" + ")<<text(am)<<move_to(355,YY-40)<<text(d)<<text(" + ")<<text(dm)<<move_to(355, YY-20)<<text(h);
}
