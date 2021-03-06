#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include "Controlled.h"

class Building : public Controlled{
public:
    void Log();
    void take_damage(int);
    void Attack();
    void mod_stats(int am, int dm, int rm);
    void Move(int x, int y){};
    void Elapse_Turn(){atkpoints=1;}
    std::map<std::string, int> get_stats();
    Building(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type);
};

#endif // BUILDING_H_INCLUDED
