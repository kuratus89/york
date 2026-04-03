#include "../stora/stora.h"
#include "chunk.h"
#include "../physics/physics.h"
#include "../windows/window.h"
#include "../stora/stora.h"

long long zombie_range =30;
queue<pair<pair<long long ,long long> ,long long>> main_hit;
long long main_hit_delay=0;

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

void main_hiter_manage(){
    if(main_hit.empty())return;
    if(main_hit.back().first.first>0)move_right(cx , cy);
    else if(main_hit.back().first.first<0)move_left(cx , cy);
    if(main_hit.back().first.second>0)move_down(cx , cy);
    else if(main_hit.back().first.second<0)move_up(cx , cy);
    ear.health-=main_hit.back().second;
    main_hit_delay=2;
    main_hit.pop();
    return;
}

void sheep(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        mo.health = 10;
    }
    gravity(mo.x , mo.y);
}


void zombie(mob &mo){
    if(!mo.initilize){
        mo.initilize =1;
        mo.health = 20;
        mo.bfs = {-1 , 0};
    }
    gravity(mo.x , mo.y);
    if(mo.delay_color)mo.delay_color--;
    else mo.color=-1;
    if(!mo.hit.empty()){
        mo.color = 0;
        mo.delay_color=2;
        if(mo.hit.back().first.first>0)move_right(mo.x , mo.y);
        else if(mo.hit.back().first.first<0)move_left(mo.x , mo.y);
        if(mo.hit.front().first.second>0)move_down(mo.x , mo.y);
        else if(mo.hit.front().first.second<0)move_down(mo.x , mo.y);
        mo.health-=mo.hit.back().second;
        mo.hit.pop();
        return;
    }    
    
    if(get_mob(mo.x-1 , mo.y)==-395){
        main_hit.push({{-1 , 0} , 1});
        return;
    }
    if(get_mob(mo.x+1  , mo.y)==-395){
        main_hit.push({{1 , 0} , 1});
        return;
    }
    if(get_mob(mo.x , mo.y+1)==-395){
        main_hit.push({{0,1} , 1});
        return;
    }
    if(get_mob(mo.x , mo.y)==-395){
        main_hit.push({{0,-1} , 1});
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
    
}

map<int, void(*)(mob&)> mober{
    {0,sheep},
    {1, zombie}
};

void mob_manager(mob &mo){
    mober[mo.type](mo);
}

void manage_hit(){
    if(main_hit_delay)
        wino.top().screen["player"][0][0].color = 0;
    else
        wino.top().screen["player"][0][0].color = player_color;
    main_hiter_manage();
    if(main_hit_delay)main_hit_delay--;
}

void spawn(int x , int y , int type , chunks *ck){
    mob mo;
    mo.type = type;
    mo.x = x;
    mo.y =y;
    (*ck).mobs.push_back(mo);
}

bool rand_spawn(int x , int y , int type , chunks *ck ){
    if(get_block(x,y))return 0;
    if(!get_block(x,y+1))return 0;
    if(rand()%1000>5)return 0;
    spawn(x , y , type , ck);
    return 1;
}
