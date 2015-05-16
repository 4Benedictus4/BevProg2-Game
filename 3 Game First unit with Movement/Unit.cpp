#include "Unit.h"

void Unit::Log(){
    gout<<color(white)<<move_to(305,YY-80)<<text("Unit type: ")<<move_to(305,YY-60)<<text("Attack: ")<<move_to(305,YY-40)<<text("Defense: ")<<move_to(305, YY-20)<<text("Health: ");
}


