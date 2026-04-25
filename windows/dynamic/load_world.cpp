#include "../window.h"
#include "../../lib.h"
#include "../../output/output.h"
#include "../../game/chunk.h"

vector<string> worlds;

void no_world(){
    win msg;
    msg.name = "msg";
    msg.stl["color"]=0;
    msg.vs["msg"] = {"There is no saved world!"};
    wino.pop();
    wino.push(msg);
}

void iptl(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = worlds.size()-1;
    if(wino.top().stl["selecter"]==worlds.size())wino.top().stl["selecter"]=0;
    if(k=="Enter"){
        if(wino.top().stl["selecter"]==worlds.size()-1)wino.pop();
        else {
            string s = worlds[wino.top().stl["selecter"]];
            win g;
            wino.pop();
            if(!ear.load("data/worlds/"+s+"/data.kp")){
                g.name = "error";
                g.sts["value"] = "cant open files , cant load the world!";
            }
            else g.name = "main_game";
            wino.push(g);
            
        }
    }
}

void load_world(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().screen_handle=1;
        fs::path pa= "data";
        pa/="worlds";
        if(!fs::exists(pa)){
            no_world();
            return;
        }
        for(auto &val:fs::directory_iterator(pa)){
            if(val.is_directory()){
                worlds.push_back(val.path().filename().string());
            }
        }
        if(worlds.empty()){
            no_world();
            return;
        }
        
        worlds.push_back(" Back");
        
    }
    option_adder(wino.top().screen["worlds"] ,worlds , wino.top().stl["selecter"], 50 , worlds.size()+4 , 1 );
    ita(wino.top().screen["screen"] , wino.top().screen["worlds"] , INT_MIN , INT_MIN , 1);
    iptl();
}