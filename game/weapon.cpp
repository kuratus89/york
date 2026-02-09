#include "../windows/window.h"
#include "../windows/dynamic/inventory.h"
#include "chunk.h"
#include "../output/output.h"

vector<string> has_weapon;
string selected_weapon = "fist";
void inpty(){
    if(k!="-"){
        if(k=="W")wino.top().stl["selecter"]--;
        if(k=="S")wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = has_weapon.size()-1;
        if(wino.top().stl["seelecter"]==has_weapon.size())wino.top().stl["selecter"] = 0;
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
            if(invoda[val.first].second=="weapon")has_weapon.push_back(invoda[val.first].first+ ":" + to_string(val.second) );
        }
        wino.top().stl["selecter"]=0;
    }
    option_adder(wino.top().screen["weapon"] , has_weapon , wino.top().stl["selecter"] , 20  , 10  );
    ita(wino.top().screen["screen"] , wino.top().screen["weapon"] , LLONG_MIN , LLONG_MIN ,1 );
    inpty();

}

void hit_right(){
    if(selected_weapon =="fist"){
        mob &mo = get_mob_id(cx+1,cy);
        if(mo.health==-1)return;
        if(mo.health==-395){
            ear.health-=1;
            return;
        }
        mo.hit.push_back({1 , 1});      
    }
}
void hit_left(){
    if(selected_weapon=="fist"){
        mob &mo = get_mob_id(cx-1 , cy);
        if(mo.health==-1)return ;
        if(mo.health==-395){
            ear.health-=1;
           return;
        }
        mo.hit.push_back({-1 , 1});                    
    }
}



