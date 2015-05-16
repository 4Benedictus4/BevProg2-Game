#ifndef CONTROLLED_H_INCLUDED
#define CONTROLLED_H_INCLUDED

#include "Tile.h"

class Controlled : public Tile {
    bool IsAc=false;
public:
    bool IsActive(){return IsAc;}
    void Activate(){IsAc=true;}
    void DeActivate(){IsAc=false;}
    virtual void mod_stats(int, int)=0;
    virtual std::map<std::string, int> get_stats()=0;
    Controlled(const int x, const int y, const int w, const int h, const int id) : Tile(x, y, w, h, id)  {}
};

#endif // CONTROLLED_H_INCLUDED
