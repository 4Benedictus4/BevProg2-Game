#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "Controlled.h"

class Unit : public Controlled{
protected:
    int atk, def, hp, range, movepoints;
    int atk_mod, def_mod;
public:
    void Log();
    void take_damage(int);
    virtual void Move(int, int);
    void mod_stats(int am, int dm);
    Unit(const int x, const int y, const int w, const int h, const int id, std::string type);
};


#endif // UNIT_H_INCLUDED
