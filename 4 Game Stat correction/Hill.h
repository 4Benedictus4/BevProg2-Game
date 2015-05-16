#ifndef HILL_H_INCLUDED
#define HILL_H_INCLUDED

#include "Landscape.h"

class Hill : public Landscape{
    int def_mod=0, atk_mod=3;
public:
    void draw();
    void Set(event);
    void Log();
    std::map<std::string, int> get_mods();
    Hill(const int x, const int y, const int w, const int h, const int id) : Landscape(x, y, w, h, id)  {}
};

#endif // HILL_H_INCLUDED
