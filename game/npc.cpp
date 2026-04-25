#include "../stora/stora.h"
#include "chunk.h"
#include "../physics/physics.h"
#include "../windows/window.h"
#include "../stora/stora.h"
#include "../windows/error.h"

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
        mo.stl["ghost"]=0;
    }
    gravity(mo.x , mo.y);
    if(!rand()%3){
        if(rand()%2)move_right(mo.x , mo.y);
        else move_left(mo.x , mo.y);
    }
}


void zombie(mob &mo){
    if(!mo.initilize){
        mo.initilize =1;
        mo.health = 20;
        mo.bfs = {-1 , 0};
        mo.stl["ghost"]=0;
    }
    gravity(mo.x , mo.y);
    if(mo.delay_color)mo.delay_color--;
    else mo.color=-1;
    if(!mo.hit.empty()){
        mo.color = 0;
        mo.delay_color=2;
        if(mo.hit.front().first.first>0)move_right(mo.x , mo.y);
        else if(mo.hit.front().first.first<0)move_left(mo.x , mo.y);
        if(mo.hit.front().first.second>0)move_down(mo.x , mo.y);
        else if(mo.hit.front().first.second<0)move_up(mo.x , mo.y);
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

void bullet(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        if(!mo.sts.count("dir"))crash("direction for bullet is invalid");
        string dir = mo.sts["dir"];
        mo.health = 1;
        mo.stl["ghost"]=1;

        if(dir=="up"){
            mo.stl["motionx"]=0;
            mo.stl["motiony"]=-1;
            mo.sts["render"] = "|";
        }
        else if(dir=="down"){
            mo.stl["motionx"]=0;
            mo.stl["motiony"]=1;
            mo.sts["render"] = "|";
        }
        else if(dir=="left"){
            mo.stl["motionx"]=-1;
            mo.stl["motiony"]=0;
            mo.sts["render"] = "-";
        }
        else if(dir=="right"){
            mo.stl["motionx"]=1;
            mo.stl["motiony"]=0;
            mo.sts["render"] = "-";
        }

    }

    if(!mo.stl["max"])mo.health =0;
    if(get_mob(mo.x+mo.stl["motionx"] , mo.y+ mo.stl["motiony"])!=-1){
        auto &it = get_mob_id(mo.x + mo.stl["motionx"] , mo.y + mo.stl["motiony"]);
        if(mo.health==-395)main_hit.push({{mo.stl["motionx"] , mo.stl["motiony"]} , 1});
        else it.hit.push({{mo.stl["motionx"] , mo.stl["motiony"]} , 1});
    }

    mo.x+=mo.stl["motionx"];
    mo.y+=mo.stl["motiony"];
    mo.stl["max"]--;
    
}

void loot(mob& mo){
    if(!mo.initilize){
        mo.initilize =1;
        mo.stl["ghost"]=1;
    }

    mo.health = INT_MAX;

    if((mo.x==cx)&&(mo.y==cy)){
        mo.health = 0;
        int iron = rand()%20+1;
        int gold = rand()%10;
        int diamond = rand()%5;
        int gun = rand()%2;
        string sm = "You got :";
        if(iron)sm+=to_string(iron) + " iron ";
        if(gold)sm+= to_string(gold) + " gold ";
        if(diamond)sm+= to_string(diamond) + " diamond ";
        if(gun) sm+= " and a gun";
        if(gun)ear.inventory[ear.inventory_str["weapon"]["pistol"]]=1;
        if(iron)ear.inventory[ear.inventory_str["block"]["iron"]]+=iron;
        if(gold)ear.inventory[ear.inventory_str["block"]["gold"]]+=gold;
        if(diamond)ear.inventory[ear.inventory_str["block"]["diamond"]]+=diamond;
        win dia;
        dia.name = "dialog";
        dia.vs["dialog"] = {sm};
        ticker.push_back({1 , dia});
    }
}

map<int, void(*)(mob&)> mober{
    {0,sheep},
    {1, zombie},
    {2 , bullet},
    {3 , loot}
};

void mob_manager(mob &mo){
    mober[mo.type](mo);
}



void manage_hit(){
    if(main_hit_delay)wino.top().screen["player"][0][0].color = 0;
    else wino.top().screen["player"][0][0].color = player_color;
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

void spawn_this_mob(mob &mo){
    (*chunk_pointer(mo.x , mo.y)).mobs.push_back(mo);
}



bool rand_spawn(int x , int y , int type , chunks *ck){
    if(get_block(x,y))return 0;
    if(!get_block(x , y+1))return 0;
    if(rand()%50000>3)return 0;
    spawn(x , y , type , ck);
    return 1;
}
