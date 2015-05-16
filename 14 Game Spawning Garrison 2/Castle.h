#ifndef CASTLE_H_INCLUDED
#define CASTLE_H_INCLUDED

#include "Building.h"

class Castle : public Building{
    std::vector<std::vector<std::vector<int> > > looks;
    bool canSpawn=true;
public:
    void Spawn_able() {canSpawn=true;}
    void Spawn_unable() {canSpawn=false;}
    bool CanSpawn() {return canSpawn;}
    void Log();
    void draw();
    std::string Spawn(event ev);
    Castle(const int x, const int y, const int w, const int h, const int id, std::string type);
};

#endif // CASTLE_H_INCLUDED
