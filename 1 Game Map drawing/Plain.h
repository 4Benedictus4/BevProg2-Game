#ifndef PLAIN_H_INCLUDED
#define PLAIN_H_INCLUDED

#include "Landscape.h"

class Plain : public Landscape{
    int def_mod=0, atk_mod=0;
public:
    void draw();
    void Set(event);
    void Log();
    std::map<std::string, int> get_mods();
    Plain(const int x, const int y, const int w, const int h, const int id) : Landscape(x, y, w, h, id)  {}
};

#endif // PLAIN_H_INCLUDED
