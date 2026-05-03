#include "../windows/window.h"
#include "../windows/error.h"
#include "../output/output.h"
#include "../game/chunk.h"
#include "skill_main.h"

void itpty(){
    if(k=="-")return;
    if(k=="W"){
        wino.top().stl["selecter"]--;
        if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["opt"].size()-1;
    }
    else if(k=="S"){
        wino.top().stl["selecter"]++;
        if(wino.top().stl["selecter"]==wino.top().vs["opt"].size())wino.top().stl["selecter"] = 0;
    }
    else if(k=="Enter"){
        if(wino.top().stl["selecter"]==wino.top().vs["opt"].size()-1)wino.pop();
        else {
            win yan;
            yan.name = "yan";
            yan.sts["desc"] = "Do you want to use ";
            if(wino.top().stl["selecter"]==0) yan.sts["desc"] += to_string(wino.top().stl["iron"]) + " Iron?";
            else if(wino.top().stl["selecter"]==1)yan.sts["desc"] += to_string(wino.top().stl["gold"]) + " Gold?";
            else if(wino.top().stl["selecter"]==2)yan.sts["desc"] += to_string(wino.top().stl["diamond"]) + " Diamond?";

            yan.vs["opt"] = {"Yes" , "No"};
            yan.sts["api"] = "buy";
            wino.push(yan);
        }
    }
}

void skill_up(){

    if(wino.top().sts.count("buy")){
        if(wino.top().sts["buy"]=="No"){
            wino.top().sts.erase("buy");
            return;
        }
        wino.top().sts.erase("buy");
        bool sus=1;
        if(ear.inventory[ear.inventory_str["block"][wino.top().vs["ouw"][wino.top().stl["selecter"]]]]<wino.top().stl[wino.top().vs["ouw"][wino.top().stl["selecter"]]])sus = 0;
        else ear.inventory[ear.inventory_str["block"][wino.top().vs["ouw"][wino.top().stl["selecter"]]]]-=wino.top().stl[wino.top().vs["ouw"][wino.top().stl["selecter"]]];
        
        if(sus){
            ear.skill[wino.top().sts["skill"]]++;
            apply_skills();
            wino.top().initilizzed = 0;
        }
        else {
            win msg;
            msg.name = "msg";
            msg.vs["msg"] = {"Insufficient " + wino.top().vs["ouw"][wino.top().stl["selecter"]]};
            wino.push(msg);
            return;
        }

        
    }

    if(!wino.top().initilizzed){
        wino.top().initilizzed = 1;
        wino.top().screen_handle=1;
        wino.top().screen["screen"] = pre_screen;
        if(!wino.top().stl.count("selecter"))wino.top().stl["selecter"]=3;
        if(!wino.top().sts.count("skill"))crash("skill not found");
        else  text_to_win_xlim(wino.top().screen["name"] , wino.top().sts["skill"] , INT_MIN);
        if(!ear.skill.count(wino.top().sts["skill"]))crash("skill data not found");
        else text_to_win_xlim(wino.top().screen["lvl"] , "Level: "+ to_string(ear.skill[wino.top().sts["skill"]]) , INT_MIN);
        text_to_win_xlim(wino.top().screen["desc"] , skill_desc[wino.top().sts["skill"]] , INT_MIN);
        text_to_win_xlim(wino.top().screen["opt_title"] , "Upgrade:" , INT_MIN);
        
        wino.top().stl["diamond"] = ((float)ear.skill[wino.top().sts["skill"]]* 1.5f);
        wino.top().stl["gold"] = wino.top().stl["diamond"]*2;
        wino.top().stl["iron"] = wino.top().stl["diamond"]*3;
        wino.top().vs["ouw"] = {
            "iron",
            "gold",
            "diamond"
        };
        wino.top().vs["wuo"] = {
            "Iron",
            "Gold",
            "Diamond"
        };
        wino.top().vs["opt"] = {
            "Iron : "+to_string(wino.top().stl["iron"]) , 
            "Gold : " + to_string(wino.top().stl["gold"]) , 
            "Diamond : " + to_string(wino.top().stl["diamond"]),
            "Back"
        };
        option_adder(wino.top().screen["opt"] , wino.top().vs["opt"] , wino.top().stl["selecter"] ,INT_MIN , INT_MIN , 0);

        horizontal_window_align(wino.top().screen["up1"] , wino.top().screen["name"] , wino.top().screen["lvl"] , 1 ,0);
        vertical_window_align(wino.top().screen["up2"] , wino.top().screen["up1"] , wino.top().screen["desc"] , 1 , 0);
        vertical_window_align(wino.top().screen["up3"] , wino.top().screen["up2"] , wino.top().screen["opt_title"] , 0 , 0);
        vertical_window_align(wino.top().screen["main"] , wino.top().screen["up3"] , wino.top().screen["opt"] , 1 , 0);
    }
    

    option_adder(wino.top().screen["opt"] , wino.top().vs["opt"] , wino.top().stl["selecter"] ,INT_MIN , INT_MIN , 0);
    vertical_window_align(wino.top().screen["main"] , wino.top().screen["up3"] ,wino.top().screen["opt"] , 1  , 0);
    bod_add(wino.top().screen["main_bod"] , wino.top().screen["main"]);
    ita(wino.top().screen["screen"] , wino.top().screen["main_bod"] ,INT_MIN , INT_MIN,0);

    itpty();
}
