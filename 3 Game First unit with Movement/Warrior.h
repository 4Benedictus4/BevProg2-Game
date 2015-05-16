#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED

#include "Unit.h"

class Warrior : public Unit{
    int atk, def, hp, range, movepoints;
    int atk_mod, def_mod;
public:
    void Log();
    void draw();
    void Move(int x, int y);
    void mod_stats(int am, int dm);
    std::map<std::string, int> get_stats();
    Warrior(const int x, const int y, const int w, const int h, const int id) : Unit(x, y, w, h, id), atk(15), def(10), hp(20), range(1), movepoints(1), atk_mod(0), def_mod(0)  {}
};


#endif // WARRIOR_H_INCLUDED
