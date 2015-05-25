#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "Player.h"
#include "Tile.h"
#include "Hourglass.h"
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
    int BuildingSize=90;
    int Usize_diff=(LandscapeSize-UnitSize)/2;
    int Bsize_diff=(LandscapeSize-BuildingSize)/2;
    std::vector<Player*> PlX;
    std::list<Tile*> TX;
    std::list<Landscape*> LX;
    std::list<Plain*> PX;
    std::list<Forest*> FX;
    std::list<Hill*> HX;
    std::list<Controlled*> CX;
    std::list<Unit*> UX;
    std::list<Building*> BX;
    std::list<Castle*> cX;
    Hourglass* H;

public:
    App();
    void Run();
};

#endif // APP_H_INCLUDED
