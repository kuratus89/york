#include "../window.h"
#include "../../game/chunk.h"
#include "../../output/output.h"

void inopyu(){
    if(k=="-")return;
    if(k=="W"){
        wino.top().stl["selecter"]--;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["item"].size() - 1;
        wino.top().stl["change"]=1;
    }
    else if(k=="S"){
        wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"] == wino.top().vs["item"].size())wino.top().stl["selecter"] =0;
        wino.top().stl["change"] = 1;
    }
    else if(k=="Enter"){
        if(wino.top().stl["selecter"] == wino.top().vs["item"].size()-1)wino.pop();
        else {
            win up;
            up.name = "itemup";
            up.sts["item"] = wino.top().vs["item"][wino.top().stl["selecter"]];
            wino.push(up);

        }
    }
}

void item(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed = 1;
        wino.top().screen_handle = 1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["change"] = 1;
        wino.top().stl["selecter"]=0;
        for(auto val:ear.inventory_str["item"]){
            if((!ear.inventory.count(val.second))||(!ear.inventory[val.second]))continue;
            wino.top().vs["item"].push_back(val.first);
        }
        if(wino.top().vs["item"].empty()){
            wino.pop();
            win msg;
            msg.name = "msg";
            msg.vs["msg"] = {"No Item In Inventory"};
            wino.push(msg);
            return;
        }
        wino.top().vs["item"].push_back("Back");
        text_to_win_xlim(wino.top().screen["title"] , "Items" , INT_MIN);
    }
    if(wino.top().stl["opt_ini"]){
        wino.top().stl["opt_ini"]=0;
        wino.top().stl["selecter"]=0;
        wino.top().vs["item"].clear();
        for(auto val:ear.inventory_str["item"]){
            if((!ear.inventory.count(val.second))||(!ear.inventory[val.second]))continue;
            wino.top().vs["item"].push_back(val.first);
        }
        if(wino.top().vs["item"].empty()){
            wino.pop();
            win msg;
            msg.name = "msg";
            msg.vs["msg"] = {"No Item In Inventory"};
            wino.push(msg);
            return;
        }
        wino.top().vs["item"].push_back("Back");
        text_to_win_xlim(wino.top().screen["title"] , "Items" , INT_MIN);

    }
    if(wino.top().stl["change"]){
        wino.top().stl["change"]=0;
        option_adder(wino.top().screen["opt"] , wino.top().vs["item"] , wino.top().stl["selecter"] ,INT_MIN , INT_MIN , 0 );
        vertical_window_align(wino.top().screen["main"] , wino.top().screen["title"] , wino.top().screen["opt"] , 1 , 0);
        bod_add(wino.top().screen["main_bod"] , wino.top().screen["main"]);
        ita(wino.top().screen["screen"] , wino.top().screen["main_bod"] , INT_MIN , INT_MIN , 0);
    }
    inopyu();
}