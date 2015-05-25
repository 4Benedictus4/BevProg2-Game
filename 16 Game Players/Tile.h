#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "graphics.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <list>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <algorithm>

//#include "App.h"

#define black 0, 0, 0
#define white 255, 255, 255
#define grey 150, 150, 150
#define red 255, 0, 0
#define green 0, 255, 0
#define blue 0, 0, 255
#define yellow 255, 255, 0

using namespace genv;

const int XX=1000, YY=600;

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
    virtual ~Tile(){}
};

#endif // TILE_H_INCLUDED
