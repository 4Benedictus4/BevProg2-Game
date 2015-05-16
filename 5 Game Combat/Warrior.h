#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED

#include "Unit.h"

class Warrior : public Unit{

public:
    void Log();
    void draw();
    Warrior(const int x, const int y, const int w, const int h, const int id, std::string type) : Unit(x, y, w, h, id, type)  {}
};


#endif // WARRIOR_H_INCLUDED
