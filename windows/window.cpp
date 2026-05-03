
// manage windows (.)-(.)

#include "boot.h"
#include "error.h"
#include "scro.h"
#include "../stora/stora.h"
#include "intro.h"
#include "../output/output.h"
#include "dynamic/intro_menu.h"
#include "dynamic/input_str.h"
#include "dynamic/msg.h"
#include "main_menu.h"
#include "dynamic/appearance.h"
#include "dynamic/input_clr.h"
#include "dynamic/settings.h"
#include "../game/main_game.h"
#include "dynamic/start_new_game.h"
#include "dynamic/load_world.h"
#include "dynamic/pause.h"
#include "dynamic/inventory.h"
#include "dynamic/cheat.h"
#include "dynamic/dialog.h"
#include "../game/weapon.h"
#include "../skill/skill_main.h"
#include "dynamic/yan.h"
#include "../skill/skill_up.h"
#include "dynamic/item.h"
#include "dynamic/itemup.h"
#include "../lib.h"



map<string , void(*)()> func_point = {
        {"boot" , boot},
        {"error", error},
        {"scro" , scro},
        {"intro" , intro},
        {"intro_menu" , intro_menu},
        {"input_str" , input_str},
        {"msg" , msg},
        {"main_menu" , main_menu},
        {"appearance" , appearance},
        {"input_clr" , input_clr},
        {"settings" , settings},
        {"main_game" , main_game},
        {"start_new_game" , start_new_game},
        {"load_world" , load_world},
        {"pause" , pause},
        {"inventory" , inventory},
        {"cheat" , cheat},
        {"dialog", dialog},
        {"weapon" , weapon},
        {"skill" , skill_main},
        {"skill_up" , skill_up},
        {"yan" , yan},
        {"item" , item},
        {"itemup" , itemup},
};




void window(){
    if(hc){
        hard_clear();
        hc=0;
    }
    if(!ticker.empty()){
        for(auto &val:ticker)val.first--;
        for(auto it = ticker.begin() ; it!=ticker.end() ;){
            if((*it).first==0){
                wino.push((*it).second);
                swap((*it) , ticker.back());
                ticker.pop_back();
            }
            else it++;
        }
    }
    if(wino.empty()){
        win tamzid;
        tamzid.type=1;
        if(first_boot)tamzid.name="boot";
        else {
            hc=1;
            tamzid.name="error";
            tamzid.sts["value"]="stack window empty";
        }
        wino.push(tamzid);
        return;
    }
    try{
        if(func_point.count(wino.top().name))func_point[wino.top().name]();
        else {
            win er;
            er.name = "error";
            er.sts["value"]= "invalid window name";
            wino.push(er);
            return;
        }
    }
    catch(exception &e){
        string s = "window -> ";
        s+=wino.top().name;
        s+= " crash , error -> ";
        s+= e.what();
        win valaray;
        valaray.name = "error";
        valaray.sts["value"]=s;
        wino.push(valaray);
        return;
    }
    

    // if(wino.top().screen_handle){
    if((!wino.empty())&&(wino.top().screen_handle)){
        kuramizer(wino.top().screen["screen"]);
    }
}

void popwin(){
    wino.pop();
}
void pushwin(win ararara){
    wino.push(ararara);
}