#ifndef HILL_H_INCLUDED
#define HILL_H_INCLUDED

#include "Landscape.h"

class Hill : public Landscape{
public:
    void draw();
    void Set(event);
    void Log();
    std::map<std::string, int> get_mods();
    Hill(const int x, const int y, const int w, const int h, const int id, std::string type) : Landscape(x, y, w, h, id, type)  {}
};

#endif // HILL_H_INCLUDED
