#ifndef FOREST_H_INCLUDED
#define FOREST_H_INCLUDED

#include "Landscape.h"

class Forest : public Landscape{
public:
    void draw();
    void Log();
    std::map<std::string, int> get_mods();
    Forest(const int x, const int y, const int w, const int h, const int id, std::string type) : Landscape(x, y, w, h, id, type)  {}
};

#endif // FOREST_H_INCLUDED
