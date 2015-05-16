#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "Controlled.h"

class Unit : public Controlled{

public:
    void Log();
    virtual void Move(int, int)=0;
    Unit(const int x, const int y, const int w, const int h, const int id) : Controlled(x, y, w, h, id)  {}
};


#endif // UNIT_H_INCLUDED
