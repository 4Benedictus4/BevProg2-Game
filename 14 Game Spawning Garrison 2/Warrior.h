#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED

#include "Unit.h"

class Warrior : public Unit{
    std::vector<std::vector<std::vector<int> > > looks;
public:
    void Log();
    void draw();
    Warrior(const int x, const int y, const int w, const int h, const int id, std::string type);
};

#endif // WARRIOR_H_INCLUDED
