#ifndef HOURGLASS_H_INCLUDED
#define HOURGLASS_H_INCLUDED

#include "Tile.h"
#include "Player.h"

class Hourglass : public Tile{
    int TurnCount=1;
    std::vector<std::vector<std::vector<int> > > looks;
    int AcP=1;
public:
    void Log();
    void draw();
    void Next_turn(){TurnCount++;}
    void Next_Player(std::vector<Player*> &PlX);
    Hourglass(const int x, const int y, const int w, const int h, const int id, std::string type);
};


#endif // HOURGLASS_H_INCLUDED
