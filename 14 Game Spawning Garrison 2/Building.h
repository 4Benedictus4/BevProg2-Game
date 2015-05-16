#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include "Controlled.h"

class Building : public Controlled{
protected:
    std::string Type;
public:
    void Log();
    void take_damage(int);
    void Attack();
    void mod_stats(int am, int dm, int rm);
    void Move(int x, int y){};
    std::map<std::string, int> get_stats();
    Building(const int x, const int y, const int w, const int h, const int id, std::string type);
};

#endif // BUILDING_H_INCLUDED
