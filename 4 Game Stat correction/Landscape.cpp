#include "Landscape.h"

void Landscape::Log(){
    gout<<color(white)<<move_to(5,YY-80)<<text("Land type: ")<<move_to(5,YY-60)<<text("Attack modifier: ")<<move_to(5,YY-40)<<text("Defense modifier: ");
}
