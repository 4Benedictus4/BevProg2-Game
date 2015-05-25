#include "Tile.h"

bool Tile::OnMouse(const int MX, const int MY){
    if(MX>X && MX<X+W && MY>Y && MY<Y+H){
        return true;
    }
    return false;
}

std::map<std::string, int> Tile::get_pos(){
    std::map<std::string, int> m;
    m["x"]=X;
    m["y"]=Y;
    return m;
}
