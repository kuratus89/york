#include "../windows/window.h"
#include "../windows/dynamic/inventory.h"
#include "chunk.h"
#include "../output/output.h"
#include "npc.h"
#include "chunk.h"

vector<string> has_weapon;
string selected_weapon = "fist";
int pre_tick_pistol=-1;
int pre_tick_kures = -1;
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

void fist(string dir){
    int mox=0;
    int moy=0;
    if(dir=="left")mox = -1;
    else if(dir=="right") mox = 1;
    else if(dir =="up")moy=-1;
    else if(dir=="down")moy = 1;
    mob &mo = get_mob_id(cx+mox , cy+moy);
    if(mo.health==-1)return;
    if(mo.health==-395)main_hit.push({{mox,moy} , 1});
    else mo.hit.push({{mox , moy} , 1});
}
void pistol(string dir){
    if(tick - pre_tick_pistol<=pistol_gap)return;
    pre_tick_pistol = tick;
    mob bul;
    bul.type = 2;
    bul.sts["dir"] = dir;
    bul.stl["max"] = max_pistol_range;
    bul.x = cx;
    bul.y = cy;
    spawn_this_mob(bul);
}
void kures(string dir){
    if(tick - pre_tick_kures<=(pistol_gap*1.5 +1))return;
    pre_tick_kures = tick;
    mob kures;
    kures.type = 7;
    kures.sts["dir"] = dir;
    kures.stl["max"] = max_pistol_range;
    kures.x = cx;
    kures.y = cy;
    spawn_this_mob(kures);
}

map<string , void(*)(string)> weapons = {
    {"fist" , fist},
    {"pistol" ,pistol},
    {"kures" , kures}
};

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
    weapons[weap]("right");
}
void hit_left(string &weap){
    weapons[weap]("left");
}
void hit_up(string &weap){
    weapons[weap]("up");
}
void hit_down(string &weap){
    weapons[weap]("down");
}





