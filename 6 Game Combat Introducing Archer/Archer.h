#ifndef ARCHER_H_INCLUDED
#define ARCHER_H_INCLUDED

#include "Unit.h"

class Archer : public Unit{

public:
    void Log();
    void draw();
    Archer(const int x, const int y, const int w, const int h, const int id, std::string type) : Unit(x, y, w, h, id, type)  {}
};

#endif // ARCHER_H_INCLUDED
