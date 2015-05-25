#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "graphics.hpp"
#include <vector>
#include <list>
#include <string>
#include <sstream>

#define white 255, 255, 255

const int XX=1000, YY=600;

class Controlled;

class Player{
    int Number;
    int Gold=20;
    int MineCount=0;
    bool IsAc=false;
    std::vector<int> C;
    std::list<Controlled*> CX;
public:
    Player(const int num);
    void Log();
    int Wealth(){return Gold;}
    void Activate(){IsAc=true;}
    void DeActivate(){IsAc=false;}
    void Elapse_Turn(){Gold+=20+MineCount*10;}               /// MINE OUTPUT INSTEAD 10!!!
    void set_property(Controlled* C){CX.push_back(C);}
    std::vector<int> Color(){return C;}
    bool IsActive(){return IsAc;}
    int Num(){return Number;}
    void mod_Gold(int);
};

#endif // PLAYER_H_INCLUDED
