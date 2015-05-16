#include "Tile.h"

bool Tile::OnMouse(const int MX, const int MY){
    if(MX>X && MX<X+W && MY>Y && MY<Y+H){
        return true;
    }
    return false;
}
