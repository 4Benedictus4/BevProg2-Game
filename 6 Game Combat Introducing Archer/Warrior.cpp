#include "Warrior.h"

void Warrior::draw(){
    if(IsActive()) gout<<move_to(X,Y)<<color(red)<<box(W, H);
    std::ifstream f;
    f.open("Warrior.txt");
    int r, g, b;
    gout<<move_to(X,Y);
    for (int i=0; i<W; i++){
            for (int j=0; j<H; j++){
                f >> r >> g >> b;
                if(r==255 && g==255 && b==255) continue;
                else gout<<color(r, g, b)<< move_to(X+i,Y+j)<<dot;
            }
    }
    f.close();
}

void Warrior::Log(){
    Unit::Log();
    std::string d, a, h, dm, am, r;
    std::stringstream ss;
    ss<<def<<" "<<atk<<" "<<hp<<" "<<def_mod<<" "<<atk_mod<<" "<<range;
    ss>>d>>a>>h>>dm>>am>>r;
    gout<<color(white)<<move_to(350,YY-85)<<text("Warrior")<<move_to(350,YY-65)<<text(a)<<text(" + ")<<text(am)<<move_to(350,YY-45)<<text(d)<<text(" + ")<<text(dm)<<move_to(350, YY-25)<<text(h)<<move_to(350, YY-5)<<text("Melee");
}








