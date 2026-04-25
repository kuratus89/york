#include "../windows/window.h"
#include "../output/output.h"
#include "../game/chunk.h"



void inpny(){
    if(k=="-")return;
    if(k=="W")wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["opt"].size() -1;
    else if(wino.top().stl["selecter"]==wino.top().vs["opt"].size())wino.top().stl["selecter"] = 0;

    if(k=="Enter"){
        if(wino.top().stl["selecter"]==wino.top().vs["opt"].size()-1)wino.pop();
        else {
            win wo;
            wo.name = "skill_up";
            wo.sts["skill"] = wino.top().vs["opt"][wino.top().stl["selecter"]];
            wino.push(wo);
        }
    }
}

void skill_main(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed = 1;
        wino.top().screen_handle = 1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"] = 0;
        wino.top().vs["opt"] = {
            "Health",
            "Mine",
            "Fist",
            "Gun",
            "Depth",
            "Back"
        };
    }
    option_adder(wino.top().screen["skill"] , wino.top().vs["opt"] , wino.top().stl["selecter"] , -1 , -1 , 1);
    text_adder(wino.top().screen["skill"] , INT_MIN , 0 , "SKILLS" , 5);
    ita(wino.top().screen["screen"] , wino.top().screen["skill"] , INT_MIN , INT_MIN , 0);
    inpny();
}

void apply_skills(){
    max_health = 100 * ear.skill["Health"];
    max_break_block = max(0, 16 - ear.skill["Mine"]);
    max_pistol_range = min(1000,5 + 5*ear.skill["Gun"]);
    pistol_gap = max(0 , 10 - (ear.skill["Gun"]/5));
}