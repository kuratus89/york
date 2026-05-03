#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
#include "../../game/chunk.h"
#include "../../game/npc.h"
void inpppt(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["opo"].size() - 1;
    if(wino.top().stl["selecter"]==wino.top().vs["opo"].size())wino.top().stl["selecter"]=0;
    if(k=="Enter"){
        if(wino.top().stl["selecter"]==3)wino.pop();
        else if(wino.top().stl["selecter"]==1)show_fps = !show_fps;
        else if(wino.top().stl["selecter"]==2)show_latency = !show_latency;
        else if(wino.top().stl["selecter"]==0){
            win yan;
            yan.name = "yan";
            yan.sts["api"] = "restart";
            yan.vs["opt"] = {
                "Yes",
                "No"
            };
            yan.sts["desc"] = "This will restart the game. Do you want to continue?";
            wino.push(yan);
            return;
        }
    }
}
void reset(){
    ear.reset();
    while(!main_hit.empty())main_hit.pop();
    main_hit_delay = 0;
}
void settings(){
    if(wino.top().sts.count("restart")){
        string s = wino.top().sts["restart"];
        wino.top().sts.erase("restart");
        if(s!="Yes")return;
        while(!wino.empty())wino.pop();
        first_boot = 1;
        return;
    }
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
        reset();
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"]=0;
        wino.top().vs["opo"] = {
            "Change Window Size",
            "Show Fps",
            "Show Latency",
            "Done"
        };
    }
    wino.top().vs["opt"] = wino.top().vs["opo"];
    if(show_fps)wino.top().vs["opt"][1]+="[Enabled]";
    else wino.top().vs["opt"][1]+="[Disabled]";
    if(show_latency)wino.top().vs["opt"][2]+="[Enabled]";
    else wino.top().vs["opt"][2]+="[Disabled]";
    option_adder(wino.top().screen["settings"] ,  wino.top().vs["opt"], wino.top().stl["selecter"] ,50 , 6,1 );
    ita(wino.top().screen["screen"], wino.top().screen["settings"] , ((x-wino.top().screen["settings"][0].size()-2)/2)+1 , ((y-wino.top().screen["settings"].size()-2)/2)+1 , 1);
    inpppt();
}