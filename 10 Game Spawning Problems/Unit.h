#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "Controlled.h"

class Unit : public Controlled{
protected:
    std::string Type;
    int movepoints;
    int range_mod;
public:
    void Log();
    void take_damage(int);
    void Attack();
    void Move(int x, int y);
    void mod_stats(int am, int dm, int rm);
    std::map<std::string, int> get_stats();
    Unit(const int x, const int y, const int w, const int h, const int id, std::string type);
};


#endif // UNIT_H_INCLUDED
