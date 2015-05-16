#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "Tile.h"
#include "Landscape.h"
#include "Plain.h"
#include "Forest.h"
#include "Hill.h"
#include "Controlled.h"
#include "Unit.h"
#include "Warrior.h"
#include "Archer.h"
#include "Building.h"
#include "Castle.h"

class App{

    int LandscapeSize=100;
    int UnitSize=80;
    int size_diff=(LandscapeSize-UnitSize)/2;
    std::vector<Tile*> TX;
    std::vector<Landscape*> LX;
    std::vector<Plain*> PX;
    std::vector<Forest*> FX;
    std::vector<Hill*> HX;
    std::vector<Controlled*> CX;
    std::vector<Unit*> UX;
    std::vector<Building*> BX;

public:
    App();
    void Run();
};

#endif // APP_H_INCLUDED
