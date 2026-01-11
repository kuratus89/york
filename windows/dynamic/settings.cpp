#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
void inpppt(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = 2;
    if(wino.top().stl["selecter"]==3)wino.top().stl["selecter"]=0;
    if(k=="Enter"){
        if(wino.top().stl["selecter"]==2){
            wino.pop();
        }
        else {
            win msg;
            msg.name = "msg";
            msg.sts["tittle"]  = "umm";
            msg.vs["msg"] = {
                "i will add it later",
                "if u really want it , then ask me"
            } ;
            msg.sts["color"]= "5";
            wino.push(msg);
        }
    }
}
void settings(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"]=0;
    }
    vector<string> optt={
        "Change Window Size",
        "more settings will be added later",
        "Done"
    };
    option_adder(wino.top().screen["settings"] ,  optt, wino.top().stl["selecter"] ,50 , 5 );
    par_scr(wino.top().screen["screen"], wino.top().screen["settings"] , ((x-wino.top().screen["settings"][0].size()-2)/2)+1 , ((y-wino.top().screen["settings"].size()-2)/2)+1);
    inpppt();
}