#include "Warrior.h"

void Warrior::draw(){
    if(IsActive()) gout<<move_to(X-2,Y-2)<<color(red)<<box(W+4, H+4);
    std::ifstream f;
    f.open("Warrior.txt");
    int r, g, b;
    gout<<move_to(X,Y);
    for (int i=0; i<H; i++)
    {
            for (int j=0; j<W; j++)
            {
                f >> r >> g >> b;
                if(r==255 && g==255 && b==255) continue;
                else gout<<color(r, g, b)<< dot <<move_to(X+i,Y+j+1);
            }
            gout<< move_to(X+i+1,Y);
    }

}

void Warrior::Log(){
    Unit::Log();
    std::string d, a, h, dm, am;
    std::stringstream ss;
    ss<<def<<" "<<atk<<" "<<hp<<" "<<def_mod<<" "<<atk_mod;
    ss>>d>>a>>h>>dm>>am;
    gout<<color(white)<<move_to(450,YY-80)<<text("Warrior")<<move_to(450,YY-60)<<text(a)<<move_to(465, YY-60)<<text(" + ")<<text(am)<<move_to(450,YY-40)<<text(d)<<move_to(465, YY-40)<<text(" + ")<<text(dm)<<move_to(450, YY-20)<<text(h);
}

std::map<std::string, int> Warrior::get_stats(){
    std::map<std::string, int> m;
}

void Warrior::mod_stats(int am, int dm){
    atk_mod=am;
    def_mod=dm;
}

void Warrior::Move(int x, int y){
    if(movepoints>0){
        X=x;
        Y=y;
    }
    //movepoints--;
    if(movepoints<=0){
        DeActivate();
    }
}


