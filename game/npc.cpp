#include "../stora/stora.h"
#include "chunk.h"
#include "../physics/physics.h"
#include "../windows/window.h"
#include "../stora/stora.h"

long long zombie_range =30;

bool bfs(long long rx , long long ry ,int range){
    queue<pair<int,int>> qe;
    qe.push({rx , ry});
    map<pair<int , int> , bool> ma;
    while(!qe.empty()){
        int bx = qe.front().first , by = qe.front().second;
        qe.pop();
        if(ma[{bx,by}])continue;
        ma[{bx,by}]=1;
        if((abs(rx-bx)>range)||(abs(ry - by)>range))continue;
        if((bx==cx)&&(by==cy))return 1;
        if(get_block(bx , by))continue;
        qe.push({bx , by+1});
        qe.push({bx+1 , by});
        qe.push({bx-1 , by});
        qe.push({bx , by-1});        
    }
    return 0;
}

void sheep(mob &mo){
    mo.health =10;
}


void zombie(mob &mo){
    if(!mo.initilize){
        mo.initilize =1;
        mo.health = 20;
        mo.bfs = {-1 , 0};
    }
    if(mo.delay_color)mo.delay_color--;
    else mo.color=-1;
    if(!mo.hit.empty()){
        mo.color = 0;
        mo.delay_color=2;
    }
    while(!mo.hit.empty()){
        if(mo.hit.back().first>0)move_right(mo.x , mo.y);
        else if(mo.hit.back().first<0)move_left(mo.x , mo.y);
        mo.health-=mo.hit.back().second;
        mo.hit.pop_back();
        return;
    }
    
    if((get_mob(mo.x-1 , mo.y)==-395)||(get_mob(mo.x+1 , mo.y)==-395)||(get_mob(mo.x , mo.y+1)==-395)||(get_mob(mo.x , mo.y-1)==-395)){
        hit();
        return;
    }
    if(mo.movement_delay){
        mo.movement_delay--;
        return;
    }
    else mo.movement_delay = 5;
    
    if(((abs(mo.x-cx)<=zombie_range)&&(abs(mo.y-cy)<=zombie_range))){
        if(block_update!=mo.bfs.first){
            if(bfs(mo.x , mo.y , zombie_range))mo.bfs.second=1;
            else mo.bfs.second=0;
        }
    }
    else mo.bfs={-1,0};
    if(mo.bfs.second){
        if(mo.x<cx){
            move_right(mo.x , mo.y);
        }
        if(mo.x>cx){
            move_left(mo.x , mo.y);
        }
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


