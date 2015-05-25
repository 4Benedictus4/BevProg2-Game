#ifndef CONTROLLED_H_INCLUDED
#define CONTROLLED_H_INCLUDED

#include "Tile.h"

class Controlled : public Tile {
protected:
    int atk, def, hp, range, atkpoints;
    int atk_mod, def_mod;
    int cost;
    Player* P;
    bool IsAc=false;
public:
    int Cost(){return cost;}
    bool IsActive(){return IsAc;}
    void Activate(){IsAc=true;}
    void DeActivate(){IsAc=false;}
    virtual void Elapse_Turn()=0;
    Player* Owner(){return P;};
    virtual void take_damage(int)=0;
    virtual void Move(int, int)=0;
    virtual void Attack()=0;
    std::string get_type(){return Type;}
    bool CanAtk();
    virtual void mod_stats(int, int, int)=0;
    virtual std::map<std::string, int> get_stats()=0;
    Controlled(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type) : Tile(x, y, w, h, id, type), P(player)  {P->set_property(this);}
    Controlled(std::string type) : Tile() {}
};

#endif // CONTROLLED_H_INCLUDED
