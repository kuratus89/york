#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
void inpppt(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = 3;
    if(wino.top().stl["selecter"]==4)wino.top().stl["selecter"]=0;
    if(k=="Enter"){
        if(wino.top().stl["selecter"]==3){
            wino.pop();
        }
        else if(wino.top().stl["selecter"]==1)show_fps = !show_fps;
        else if(wino.top().stl["selecter"]==2)show_latency = !show_latency;
    }
}
void settings(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
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
    option_adder(wino.top().screen["settings"] ,  wino.top().vs["opt"], wino.top().stl["selecter"] ,50 , 6 );
    ita(wino.top().screen["screen"], wino.top().screen["settings"] , ((x-wino.top().screen["settings"][0].size()-2)/2)+1 , ((y-wino.top().screen["settings"].size()-2)/2)+1 , 1);
    inpppt();
}