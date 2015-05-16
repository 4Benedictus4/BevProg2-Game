#ifndef LANDSCAPE_H_INCLUDED
#define LANDSCAPE_H_INCLUDED

#include "Tile.h"

class Landscape : public Tile {
    bool IsOcc=false;
public:
    bool IsOccupied(){return IsOcc;}
    void Occupy(){IsOcc=true;}
    void UnOccupy(){IsOcc=false;}
    void Log();
    virtual std::map<std::string, int> get_mods()=0;
    Landscape(const int x, const int y, const int w, const int h, const int id) : Tile(x, y, w, h, id)  {}
};

#endif // LANDSCAPE_H_INCLUDED
