#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

class Player{
    int Number;
    int Gold=20;
    bool IsAc=false;
    std::vector<int> C;
public:
    Player(const int num);
    void Activate(){IsAc=true;}
    void DeActivate(){IsAc=false;}
    std::vector<int> Color(){return C;}
    bool IsActive(){return IsAc;}
    int Num(){return Number;}
    void mod_Gold(int);
};

#endif // PLAYER_H_INCLUDED
