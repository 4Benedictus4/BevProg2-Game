#ifndef CASTLE_H_INCLUDED
#define CASTLE_H_INCLUDED

#include "Building.h"

class Castle : public Building{
    std::vector<std::vector<std::vector<int> > > looks;
    bool canSpawn=true;
    int spawnpoints=1;
public:
    void Spawn_able() {canSpawn=true;}
    void Spawn_unable() {canSpawn=false;}
    bool CanSpawn();
    void Elapse_Turn();
    void Log();
    void draw();
    std::string Spawn(event ev);
    Castle(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type);
};

#endif // CASTLE_H_INCLUDED
