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


}

std::map<std::string, int> Warrior::get_stats(){

}

void Warrior::mod_stats(int am, int dm){
    atk_mod=am;
    def_mod=dm;
}


