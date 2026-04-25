#include "../windows/window.h"
#include "../windows/dynamic/inventory.h"
#include "chunk.h"
#include "../output/output.h"
#include "npc.h"
#include "chunk.h"

vector<string> has_weapon;
string selected_weapon = "fist";
int pre_tick_pistol=-1;
void inpty(){
    if(k!="-"){
        if(k=="W")wino.top().stl["selecter"]--;
        if(k=="S")wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = has_weapon.size()-1;
        if(wino.top().stl["selecter"]==has_weapon.size())wino.top().stl["selecter"] = 0;
        if(k=="Enter"){
            selected_weapon = has_weapon[wino.top().stl["selecter"]];
            wino.pop();
        }
    }
}

void weapon(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed =1;
        wino.top().screen_handle =1;
        wino.top().screen["screen"] = pre_screen;
        has_weapon.clear();
        has_weapon.push_back("fist");
        // for(auto val:ear.inventory){
        for(auto val:ear.inventory){
            if(val.second<=0)continue;
            // if(invoda[val.first].second=="weapon")has_weapon.push_back(invoda[val.first].first+ ":" + to_string(val.second) );
            if(invoda[val.first].second=="weapon")has_weapon.push_back(invoda[val.first].first);
        }
        wino.top().stl["selecter"]=0;
    }
    option_adder(wino.top().screen["weapon"] , has_weapon , wino.top().stl["selecter"] , 20  , 10 ,1 );
    ita(wino.top().screen["screen"] , wino.top().screen["weapon"] , INT_MIN , INT_MIN ,1 );
    inpty();

}

void hit_right(string &weap){
    if(weap =="fist"){
        mob &mo = get_mob_id(cx+1,cy);
        if(mo.health==-1)return;
        if(mo.health==-395)main_hit.push({{1,0} ,  1 });
        else mo.hit.push({{1,0} , ear.skill["Fist"]});      
    }
    if(weap =="pistol"){
        if(tick - pre_tick_pistol<=pistol_gap)return;
        pre_tick_pistol = tick;
        mob bul;
        bul.type = 2;
        bul.sts["dir"] = "right";
        bul.stl["max"]=max_pistol_range;
        bul.x = cx;
        bul.y = cy;
        spawn_this_mob(bul);
    }
}
void hit_left(string &weap){
    if(weap=="fist"){
        mob &mo = get_mob_id(cx-1 , cy);
        if(mo.health==-1)return ;
        if(mo.health==-395)main_hit.push({{-1,0},1});
        else mo.hit.push({{-1,0} , ear.skill["Fist"]});                    
    }
    else if(weap=="pistol"){
        if(tick - pre_tick_pistol<=pistol_gap)return;
        pre_tick_pistol = tick;
        mob mo;
        mo.type = 2;
        mo.x = cx;
        mo.y=cy;
        mo.sts["dir"] = "left";
        mo.stl["max"] = max_pistol_range;
        spawn_this_mob(mo);
    }
}
void hit_up(string &weap){
    if(weap=="fist"){
        mob &mo = get_mob_id(cx , cy-1);
        if(mo.health==-1)return;
        if(mo.health==-395)main_hit.push({{0,-1} , 1});
        else mo.hit.push({{0,-1} , ear.skill["Fist"]});
    }
    else if(weap=="pistol"){
        if(tick - pre_tick_pistol<=pistol_gap)return ;
        pre_tick_pistol = tick;
        mob mo;
        mo.type = 2;
        mo.x = cx;
        mo.y = cy;
        mo.sts["dir"]="up";
        mo.stl["max"] = max_pistol_range;
        spawn_this_mob(mo);
    }
}

void hit_down(string &weap){
    if(weap=="fist"){
        mob &mo = get_mob_id(cx , cy+1);
        if(mo.health==-1)return;
        if(mo.health==-395)main_hit.push({{0,1} , 1});
        else mo.hit.push({{0,1} , ear.skill["Fist"]});
    }
    else if(weap == "pistol"){
        if(tick - pre_tick_pistol<=pistol_gap)return ;
        pre_tick_pistol = tick;
        mob mo;
        mo.type = 2;
        mo.x = cx;
        mo.y = cy;
        mo.sts["dir"]="down";
        mo.stl["max"] = max_pistol_range;
        spawn_this_mob(mo);
    }

}





