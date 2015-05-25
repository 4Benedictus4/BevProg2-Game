#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Player.h"

using namespace genv;

class Tile{
protected:
    int X, Y, W, H, ID;
public:
    virtual void draw()=0;
    virtual bool OnMouse(const int, const int);
    virtual void Set(event){}
    virtual void Log(){}
    std::map<std::string, int> get_pos();
    Tile(const int x, const int y, const int w, const int h, const int id) : X(x), Y(y), W(w), H(h), ID(id) {}
    Tile(){}
    virtual ~Tile(){}
};

#endif // TILE_H_INCLUDED
