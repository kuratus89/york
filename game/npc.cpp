#include "../stora/stora.h"
#include "chunk.h"
#include "../physics/physics.h"
#include "../windows/window.h"
#include "../stora/stora.h"
#include "../windows/error.h"
#include "../output/output.h"

long long zombie_range =30;
queue<pair<pair<long long ,long long> ,long long>> main_hit;
long long main_hit_delay=0;

void spawn_this_mob(mob &mo){
    (*chunk_pointer(mo.x , mo.y)).mobs.push_back(mo);
}

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
bool manage_mob_hit(mob &mo , bool knockback){
    if(mo.hit.empty())return 0;
    
    mo.color = 0;
    mo.delay_color = 2;
    mo.health -= mo.hit.front().second;
    mo.hit.pop();
    if(!knockback)return 1;
    if(mo.hit.front().first.first>0)move_right(mo.x , mo.y);
    else if(mo.hit.front().first.first<0)move_left(mo.x , mo.y);
    if(mo.hit.front().first.second>0)move_down(mo.x , mo.y);
    else if(mo.hit.front().first.second<0)move_up(mo.x , mo.y);
    
    return 1;
}


void sheep(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        mo.health = 10;
        mo.stl["ghost"]=0;
        mo.stl["tick"]=tick;
        mo.stl["dir"] = rand()%2;
        int r = rand()%5 +1;
        for(int i=0 ; i<r ; i++)mo.kill_reward.push_back(ear.inventory_str["item"]["food"]);
    }
    if(mo.delay_color)mo.delay_color--;
    else mo.color = -1;
    manage_mob_hit(mo , 1);
    gravity(mo.x , mo.y);
    if(tick- mo.stl["tick"]<30)return;
    mo.stl["tick"] = tick;
    if(rand()%5){
        // if(rand()%2)return;
        if(mo.stl["dir"])move_left(mo.x , mo.y);
        else move_right(mo.x , mo.y);
    }
    else mo.stl["dir"] = !(mo.stl["dir"]);
}


void zombie(mob &mo){
    if(!mo.initilize){
        mo.initilize =1;
        mo.health = 20;
        mo.bfs = {-1 , 0};
        mo.stl["ghost"]=0;
        if(rand()%2)mo.kill_reward.push_back(ear.inventory_str["block"]["gold"]);
        if(rand()%2)mo.kill_reward.push_back(ear.inventory_str["item"]["food"]);
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
        mo.health-=mo.hit.front().second;
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
    manage_mob_hit(mo , 0);

    if(!mo.stl["max"])mo.health =0;
    if((get_mob(mo.x+mo.stl["motionx"] , mo.y+ mo.stl["motiony"])!=-1)&&(!get_mob_id(mo.x+mo.stl["motionx"] , mo.y + mo.stl["motiony"]).stl["ghost"])){
        auto &it = get_mob_id(mo.x + mo.stl["motionx"] , mo.y + mo.stl["motiony"]);
        if(it.health==-395)main_hit.push({{mo.stl["motionx"] , mo.stl["motiony"]}  , 1});
        else it.hit.push({{mo.stl["motionx"] , mo.stl["motiony"]} , 1});
        mo.health =0;
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
        int heal = !(rand()%5);
        string sm = "You got :";
        if(iron)sm+=to_string(iron) + " iron ";
        if(gold)sm+= to_string(gold) + " gold ";
        if(diamond)sm+= to_string(diamond) + " diamond ";
        if(heal)sm+= to_string(heal)+ " Heal";
        if(gun) sm+= " and a gun";
        if(gun)ear.inventory[ear.inventory_str["weapon"]["pistol"]]=1;
        if(iron)ear.inventory[ear.inventory_str["block"]["iron"]]+=iron;
        if(gold)ear.inventory[ear.inventory_str["block"]["gold"]]+=gold;
        if(diamond)ear.inventory[ear.inventory_str["block"]["diamond"]]+=diamond;
        if(heal)ear.inventory[ear.inventory_str["item"]["heal"]]+=heal;
        win dia;
        dia.name = "dialog";
        dia.vs["dialog"] = {sm};
        ticker.push_back({1 , dia});
    }
}

void grave(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        mo.stl["ghost"]=1;
    }

    mo.health = INT_MAX;

    if((mo.x == cx)&&(mo.y==cy)){
        mo.health = 0;
        map<int , int> ma;
        for(auto val:mo.kill_reward)ma[val]++;
        for(auto val:ma)ear.inventory[val.first]+=val.second;
        string sm = "You got : ";
        for(auto val:ma) sm+= to_string(val.second) + " "+ invoda[val.first].first + ", ";
        win dia;
        dia.name = "dialog";
        dia.vs["dialog"] = {sm};
        ticker.push_back({1 , dia});
        
    }
}

void bures(mob &mo){
    if(!mo.initilize){
        mo.initilize=1;
        mo.health = 150;
        mo.stl["boss"]=1;
        mo.stl["max_health"] = mo.health;
        mo.sts["name"] = "BURES";
        mo.stl["ghost"]=0;
        mo.stl["tick"] = tick;
        mo.kill_reward.push_back(ear.inventory_str["weapon"]["kures"]);
    }
    if(!mo.hit.empty()){
        mo.color = 0;
        mo.delay_color = 2;
        if(mo.hit.front().first.first>0)move_right(mo.x , mo.y);
        else if(mo.hit.front().first.first<0)move_left(mo.x , mo.y);
        if(mo.hit.front().first.second>0)move_down(mo.x , mo.y);
        else if(mo.hit.front().first.second<0)move_up(mo.x , mo.y);
        mo.health -=mo.hit.front().second;
        mo.hit.pop();
    }

    if((abs(cx - mo.x)>100)||(abs(cy - mo.y)>50))return;
    if(tick - mo.stl["tick"]<50)return;
    mo.stl["tick"]= tick;
    mob kures;
    kures.type = 6;
    kures.x = mo.x;
    kures.y = mo.y;
    spawn_this_mob(kures);
}

void kures_mob(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        mo.health =1;
        mo.stl["ghost"] = 1;
        mo.stl["x"] = cx;
        mo.stl["y"] = cy;
    }
    manage_mob_hit(mo , 0);
    if((abs(mo.x - cx)<10)&&(abs(mo.y - cy)<10)){
        mo.stl["x"] = cx;
        mo.stl["y"] = cy;
    }
    if(((mo.x==mo.stl["x"])&&(mo.y==mo.stl["y"]))||((mo.x==cx)&&(mo.x==cy))){
        for(int i= mo.x-1 ; i<=mo.x +1 ; i++){
            for(int j = mo.y - 1 ; j<=mo.y +1 ; j++){
                set_block(i , j , 0);
                if((i==cx)&&(j==cy))main_hit.push({{0,0} , 10});
            }
        }
        mo.health = 0;
        return;
    }
    int x = mo.stl["x"] - mo.x;
    int y = mo.stl["y"] - mo.y;
    if(x>0)mo.x++;
    else if(x<0)mo.x--;
    if(y>0)mo.y++;
    else if(y<0)mo.y--;

}

void kures(mob &mo){
    if(!mo.initilize){
        mo.initilize = 1;
        mo.health = 1;
        mo.stl["ghost"]=1;
        mo.stl["mox"]=0;
        mo.stl["moy"]=0;
        if(mo.sts["dir"]=="right")mo.stl["mox"]=1;
        else if(mo.sts["dir"]=="left")mo.stl["mox"]=-1;
        else mo.stl["mox"]=0;
        if(mo.sts["dir"]=="up")mo.stl["moy"] = -1;
        else if(mo.sts["dir"]=="down") mo.stl["moy"] = 1;
        else mo.stl["moy"]=0;
    }
    mo.stl["max"]--;
    manage_mob_hit(mo , 0);

    chunks *mid = chunk_pointer(mo.x , mo.y);
    chunks *side;
    chunks *side2;
    if((mo.sts["dir"]=="left")||(mo.sts["dir"]=="right")){
        side = chunk_pointer(mo.x , mo.y + chunk_size);
        side2 = chunk_pointer(mo.x , mo.y - chunk_size);
    }
    else {
        side = chunk_pointer(mo.x+ chunk_size , mo.y);
        side2 = chunk_pointer(mo.x - chunk_size , mo.y);
    }

    int tarx;
    int tary;
    bool found = 0;
    if(mid->mobs.size()>1){
        pair<int , pair<int , int>> move = {INT_MAX , {0,0}};
        for(auto &val: mid->mobs){
            if(val.stl["ghost"])continue;
            int dix = abs(mo.x - val.x);
            int diy = abs(mo.y - val.y);
            int dis = (dix*dix) + (diy*diy);
            if(move.first<dis)continue;
            move = {dis , {val.x , val.y}};
            found = 1;
        }
        tarx = move.second.first;
        tary = move.second.second;
    }
    if(!found){
        pair<int , pair<int , int>> move = {INT_MAX , {0,0}};
        for(auto &val:side->mobs){
            if(val.stl["ghost"])continue;
            found =1;
            int dix = abs(mo.x - val.x);
            int diy = abs(mo.y - val.y);
            int dis = (dix*dix) + (diy*diy);
            if(move.first<dis)continue;
            move = {dis ,  {val.x , val.y}};
        }
        for(auto &val:side2->mobs){
            if(val.stl["ghost"])continue;
            found =1;
            int dix = abs(mo.x - val.x);
            int diy = abs(mo.y - val.y);
            int dis = (dix*dix)+(diy*diy);
            if(move.first<dis)continue;
            move = {dis , {val.x , val.y}};
        }
        tarx = move.second.first;
        tary = move.second.second;
    }
    if(((mo.x==tarx)&&(mo.y==tary))||!(mo.stl["max"])){
        for(int i=mo.x-1 ; i<=mo.x+1 ; i++){
            for(int j= mo.y-1 ; j<=mo.y+1 ; j++){
                set_block(i , j , 0);
                if(get_mob(i , j)!=-1)get_mob_id(i , j).hit.push({{0,0} , 3});
            }
        }
        mo.health=0;
        return;
    }
    int movex=0;
    int movey=0;
    if(found){
        if(tarx!=mo.x)movex=((tarx - mo.x)/abs(tarx - mo.x));
        if(tary!=mo.y)movey=((tary - mo.y)/abs(tary -mo.y));
    }
    else {
        movex = mo.stl["mox"];
        movey = mo.stl["moy"];
    }
    mo.x+=movex;
    mo.y+=movey;
}

map<int, void(*)(mob&)> mober{
    {0,sheep},
    {1, zombie},
    {2 , bullet},
    {3 , loot},
    {4 , grave},
    {5 , bures},
    {6 , kures_mob},
    {7 , kures},
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





bool rand_spawn(int x , int y , int type , chunks *ck){
    if(get_block(x,y))return 0;
    if(!get_block(x , y+1))return 0;
    if(rand()%50000>3)return 0;
    spawn(x , y , type , ck);
    return 1;
}

void kill_mob(mob &mo){
    if(mo.hit.empty())return;

}

void boss_title(vector<vector<pixel>> &scr , mob &mo){
    if(scr.empty())return;
    if(!mo.stl.count("max_health"))return;
    if((!mo.stl.count("max_health"))||(mo.stl["max_health"]==0))return;
    if(!mo.sts.count("name"))return;
    int max = mo.stl["max_health"];
    int sx = scr[0].size()/2;
    pixel pe;
    pe.color = 5;
    pe.value = " ";
    vector<vector<pixel>> title;
    vector<vector<pixel>> health = vector<vector<pixel>>(1 , vector<pixel>(sx , pe));
    vector<vector<pixel>> name;
    text_to_win_xlim(name , mo.sts["name"] , INT_MIN);
    if((((float)mo.health)/((float)max))>0.6f)pe.color =  2;
    else if((((float)mo.health)/((float)max))>0.35f)pe.color = 1;
    else pe.color = 0;
    pe.value = "█";
    int cnt  = (((float)mo.health)/(float)max)*sx;
    for(int i=0 ; i<cnt ; i++)health[0][i] = pe;

    bod_add(title , health);
    ita(title , name , INT_MIN , 0 , 0);
    ita(scr , title , INT_MIN , 1 , 0);   

}
