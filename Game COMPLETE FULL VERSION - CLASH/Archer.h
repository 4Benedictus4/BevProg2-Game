#ifndef ARCHER_H_INCLUDED
#define ARCHER_H_INCLUDED

#include "Unit.h"

class Archer : public Unit{
    std::vector<std::vector<std::vector<int> > > looks;
public:
    void Log();
    void draw();
    Archer(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type);
};

#endif // ARCHER_H_INCLUDED
