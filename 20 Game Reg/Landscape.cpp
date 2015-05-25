#include "Landscape.h"

Landscape::Landscape(const int x, const int y, const int w, const int h, const int id, std::string type) : Tile(x, y, w, h, id, type)  {
    Type=type;
    if(type=="p"){
        def_mod=0;
        atk_mod=0;
        range_mod=0;
    }
    if(type=="f"){
        def_mod=2;
        atk_mod=0;
        range_mod=0;
    }
    if(type=="h"){
        def_mod=0;
        atk_mod=2;
        range_mod=1;
    }
}

void Landscape::Log(){
    gout<<color(white)<<move_to(5,YY-85)<<text("Land type: ")<<move_to(5,YY-65)<<text("Attack modifier: ")<<move_to(5,YY-45)<<text("Defense modifier: ")<<move_to(5,YY-25)<<text("Range modifier: ");
}
