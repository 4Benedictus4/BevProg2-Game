#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "Controlled.h"

class Unit : public Controlled{
    bool DidMove=false;
    int atk, def, hp;
    int atk_mod, def_mod;
public:
    void Log();
    Unit(const int x, const int y, const int w, const int h, const int id, std::string type);

};


#endif // UNIT_H_INCLUDED
