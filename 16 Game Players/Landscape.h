#ifndef LANDSCAPE_H_INCLUDED
#define LANDSCAPE_H_INCLUDED

#include "Tile.h"

class Landscape : public Tile {
protected:
    bool IsOcc=false;
    int def_mod, atk_mod, range_mod;
public:
    bool IsOccupied(){return IsOcc;}
    void Occupy(){IsOcc=true;}
    void UnOccupy(){IsOcc=false;}
    void Log();
    virtual std::map<std::string, int> get_mods()=0;
    Landscape(const int x, const int y, const int w, const int h, const int id, std::string type);
};

#endif // LANDSCAPE_H_INCLUDED
