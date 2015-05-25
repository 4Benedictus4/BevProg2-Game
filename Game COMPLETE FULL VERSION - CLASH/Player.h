#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "graphics.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <algorithm>

#define black 0, 0, 0
#define white 255, 255, 255
#define grey 150, 150, 150
#define red 255, 0, 0
#define green 0, 255, 0
#define blue 0, 0, 255
#define yellow 255, 255, 0

const int XX=1000, YY=600;

class Controlled;

class Player{
    int Number;
    int Gold=20;
    int MerchantCount=0;
    int M_Cost=50;
    bool IsAc=false;
    std::vector<int> C;             /// Player color
    std::list<Controlled*> CX;      /// Player controlled
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
