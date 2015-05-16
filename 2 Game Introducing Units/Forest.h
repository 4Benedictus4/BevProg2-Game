#ifndef FOREST_H_INCLUDED
#define FOREST_H_INCLUDED

#include "Landscape.h"

class Forest : public Landscape{
    int def_mod=3, atk_mod=0;
public:
    void draw();
    void Set(event);
    void Log();
    std::map<std::string, int> get_mods();
    Forest(const int x, const int y, const int w, const int h, const int id) : Landscape(x, y, w, h, id)  {}
};

#endif // FOREST_H_INCLUDED
