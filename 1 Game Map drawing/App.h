#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "Tile.h"
#include "Landscape.h"
#include "Plain.h"
#include "Forest.h"
#include "Hill.h"

class App{

    int LandscapeSize=100;
    int UnitSize=80;
    int BuildingSize=100;
    std::vector<Tile*> TILES;
    std::vector<Landscape*> LANDSCAPES;
    std::vector<Plain*> PLAINS;
    std::vector<Forest*> FORESTS;
    std::vector<Hill*> HILLS;

public:
    App();
    void Run();
};

#endif // APP_H_INCLUDED
