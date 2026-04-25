#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
#include "../../game/chunk.h"

void inp(int sil){
    if((k=="W"))wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]==sil)wino.top().stl["selecter"]=0;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"]=sil-1;
    if(k=="Enter"){

        if(wino.top().stl["selecter"]==sil-1){
            wino.pop();
            return;
        }

        if(wino.top().stl["selecter"]==0)speed = !speed;
        if(wino.top().stl["selecter"]==1)ghost = !ghost;
        if(wino.top().stl["selecter"]==2)ear.inventory[5] = 999999;
        if(wino.top().stl["selecter"]==3)ear.inventory[ear.inventory_str["weapon"]["pistol"]]=1;
        if(wino.top().stl["selecter"]==4)ear.health = max_health;
        win msg;
        msg.name = "msg";
        msg.vs["msg"] = {"Cheat Executed"};
        wino.push(msg);
    }
}


void cheat(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed =1;
        wino.top().screen_handle =1;
        wino.top().type=0;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"]=0;
    }
    
    vector<string> opts = {
        "Speed!!",
        "Ghost!!",
        "givme diamonds!",
        "givme pistol",
        "max health",
        "Back"
    };
    if(!speed)opts[0]+="[Disabled]";
    else opts[0]+="[Enabled]";

    if(!ghost)opts[1]+="[Disabled]";
    else opts[1]+="[Enabled]";

    option_adder(wino.top().screen["cheat"], opts ,wino.top().stl["selecter"] , 30,10 , 1);
    ita(wino.top().screen["screen"] , wino.top().screen["cheat"] , INT_MIN , INT_MIN , 1);
    inp(opts.size());
}