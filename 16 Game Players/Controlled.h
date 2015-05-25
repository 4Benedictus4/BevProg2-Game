#ifndef CONTROLLED_H_INCLUDED
#define CONTROLLED_H_INCLUDED

#include "Tile.h"
#include "Player.h"

class Controlled : public Tile {
protected:
    int atk, def, hp, range, atkpoints;
    int atk_mod, def_mod;
    Player* P;
    bool IsAc=false;
public:
    bool IsActive(){return IsAc;}
    void Activate(){IsAc=true;}
    void DeActivate(){IsAc=false;}
    Player* Owner(){return P;}
    virtual void take_damage(int)=0;
    virtual void Move(int, int)=0;
    virtual void Attack()=0;
    virtual void mod_stats(int, int, int)=0;
    virtual std::map<std::string, int> get_stats()=0;
    Controlled(const int x, const int y, const int w, const int h, const int id, Player* player) : Tile(x, y, w, h, id), P(player)  {}
};

#endif // CONTROLLED_H_INCLUDED
