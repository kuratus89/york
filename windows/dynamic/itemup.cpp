#include "../window.h"
#include "../error.h"
#include "../../game/chunk.h"
#include "../../output/output.h"


void heal(){
    ear.health = max_health;
}
void food(){
    ear.health = min(max_health , ear.health +10);
}

map<string , void(*)()>  item_point = {
    {"heal" , heal},
    {"food" , food}
};

void ittuo(){
    if(k=="-")return;
    if(k=="W"){
        wino.top().stl["selecter"]--;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["opt"].size() -1;
        wino.top().stl["update"] = 1;
    }
    else if(k=="S"){
        wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]==wino.top().vs["opt"].size())wino.top().stl["selecter"] = 0;
        wino.top().stl["update"]=1;
    }
    else if(k=="Enter"){
        if(wino.top().stl["selecter"]==wino.top().vs["opt"].size() -1)wino.pop();
        else{
            item_point[wino.top().sts["item"]]();
            ear.inventory[ear.inventory_str["item"][wino.top().sts["item"]]]--;
            wino.pop();
        }
    }
}

void itemup(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed = 1;
        wino.top().screen_handle = 1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"] =0;
        wino.top().stl["update"] = 1;
        wino.top().vs["opt"] = {
            "Use",
            "Back"
        };
        if(!wino.top().sts.count("item"))crash("Item not found");
        if(!item_desc.count(wino.top().sts["item"]))crash("Item data not found");
        if(!item_point.count(wino.top().sts["item"]))crash("Item Process Data Not Found");
        text_to_win_xlim(wino.top().screen["title"] , wino.top().sts["item"] , INT_MIN);
        text_to_win_xlim(wino.top().screen["count"] , "  Quantity : "+ to_string(ear.inventory[ear.inventory_str["item"][wino.top().sts["item"]]]) , INT_MIN);
        text_to_win_xlim(wino.top().screen["desc"] , item_desc[wino.top().sts["item"]] , INT_MIN);
        vertical_window_align(wino.top().screen["tc"] , wino.top().screen["title"] , wino.top().screen["count"] , 1 , 0);
        vertical_window_align(wino.top().screen["up"] , wino.top().screen["tc"] , wino.top().screen["desc"] , 1 , 0);
    }
    if(ear.inventory[ear.inventory_str["item"][wino.top().sts["item"]]]<=0){
        wino.pop();
        wino.top().stl["opt_ini"]=1;
        return;
    }
    if(wino.top().stl["update"]){
        wino.top().stl["update"]=0;
        option_adder(wino.top().screen["opt"] , wino.top().vs["opt"] , wino.top().stl["selecter"] , INT_MIN , INT_MIN , 0 );
        vertical_window_align(wino.top().screen["main"] , wino.top().screen["up"] , wino.top().screen["opt"] , 1 , 0);
        bod_add(wino.top().screen["main_bod"] , wino.top().screen["main"]);
        ita(wino.top().screen["screen"] , wino.top().screen["main_bod"] , INT_MIN , INT_MIN , 0);
    }
    ittuo();
}

