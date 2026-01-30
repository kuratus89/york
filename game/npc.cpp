#include "../stora/stora.h"
#include "chunk.h"
#include "../physics/physics.h"

void sheep(mob &mo){
    mo.health =10;
}


void zombie(mob &mo){
    if(!mo.initilize){
        mo.health = 20;
    }
    if(cx>mo.x){
        move_right(mo.x , mo.y);
    }
    else if(cx<mo.x){
        move_left(mo.x , mo.y);
    }
    gravity(mo.x , mo.y);
}

map<int, void(*)(mob&)> mober{
    {0,sheep},
    {1, zombie}
};

void mob_manager(mob &mo){
    mober[mo.type](mo);
}


