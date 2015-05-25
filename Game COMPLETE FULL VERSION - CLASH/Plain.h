#ifndef PLAIN_H_INCLUDED
#define PLAIN_H_INCLUDED

#include "Landscape.h"

class Plain : public Landscape{
public:
    void draw();
    void Log();
    std::map<std::string, int> get_mods();
    Plain(const int x, const int y, const int w, const int h, const int id, std::string type) : Landscape(x, y, w, h, id, type)  {}
};

#endif // PLAIN_H_INCLUDED
