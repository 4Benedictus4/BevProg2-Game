#ifndef CASTLE_H_INCLUDED
#define CASTLE_H_INCLUDED

#include "Building.h"

class Castle : public Building{
    std::vector<std::vector<std::vector<int> > > looks;
public:
    void Log();
    void draw();
    Castle(const int x, const int y, const int w, const int h, const int id, std::string type);
};

#endif // CASTLE_H_INCLUDED
