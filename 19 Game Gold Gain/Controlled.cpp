#include "Controlled.h"

bool Controlled::CanAtk(){
    if(atkpoints>0) return true;
    else return false;
}
