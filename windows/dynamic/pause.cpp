#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
#include "../../game/chunk.h"

void itt(){
    if(k=="W")wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = 2;
    if(wino.top().stl["selecter"]==3)wino.top().stl["selecter"]=0;

    if(k=="Enter"){
        if(wino.top().stl["selecter"]==0)wino.pop();
        if(wino.top().stl["selecter"]==1){
            win al;
            if(!save_game("data/worlds/"+ear.name+"/data.kp")){
                al.name = "error";
                al.sts["value"] = "cant write files , cant save world!";
            }
            else {
                al.name = "msg";
                al.vs["msg"] = {"game saved!"};
                al.stl["color"]=1;
            }
            wino.push(al);
        }
        if(wino.top().stl["selecter"]==2){
            win che;
            che.name = "cheat";
            wino.push(che);
        }
    }
}

void pause(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle =1;
        wino.top().screen["screen"] = pre_screen;
    }
    vector<string> opts= {
        "Resume",
        "Save",
        "Cheats"
    };
    option_adder(wino.top().screen["pau"] , opts , wino.top().stl["selecter"] , 30 , 5);
    ita(wino.top().screen["screen"] ,wino.top().screen["pau"] , LLONG_MIN , LLONG_MIN , 1);
    itt();
}