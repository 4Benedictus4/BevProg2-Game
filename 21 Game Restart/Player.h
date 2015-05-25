#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "graphics.hpp"
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>

#define white 255, 255, 255

const int XX=1000, YY=600;

class Controlled;

class Player{
    int Number;
    int Gold=20;
    int MerchantCount=0;
    int M_Cost=50;
    bool IsAc=false;
    std::vector<int> C;
    std::list<Controlled*> CX;
public:
    Player(const int num);
    void Log();
    int Wealth(){return Gold;}
    int Merchant_Cost(){return M_Cost;}
    void mod_Mcost(int a){M_Cost+=a;}
    void Activate(){IsAc=true;}
    void CallMerchant(){MerchantCount++;}
    void DeActivate(){IsAc=false;}
    void Elapse_Turn(){Gold+=20+MerchantCount*5;}               /// + MINE OUTPUT AFTER CREATING MINES!!!
    void set_property(Controlled* C){CX.push_back(C);}
    void C_death(Controlled* c){CX.erase(std::remove(CX.begin(), CX.end(), c), CX.end());}
    std::list<Controlled*> Army(){return CX;}
    std::vector<int> Color(){return C;}
    bool IsActive(){return IsAc;}
    int Num(){return Number;}
    void mod_Gold(int);
};

#endif // PLAYER_H_INCLUDED
