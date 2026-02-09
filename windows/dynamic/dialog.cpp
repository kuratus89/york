#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"
#include "../../physics/physics.h"
#include "../../input/input.h"

void dialog(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed =1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().screen_handle=1;
        wino.top().stl["cx"]=0;
        wino.top().stl["cy"]=0;
        wino.top().screen["dialog"] = bod_create(5 , x , 5);
        for(long long i=1 ; i<5-1; i++)wino.top().screen["dialog"][i][8].value = "|";
        wino.top().screen["dialog"][1][5].color = wino.top().stl["player_color"];
        wino.top().screen["dialog"][1][5].value = wino.top().sts["player"];
        long long temp = 1;
        for(auto val:wino.top().sts["name"]){
            wino.top().screen["dialog"][2][temp].value = val;
            temp++;
        }
        wino.top().stl["tempx"]=0;
        wino.top().stl["tempy"]=0;
        pixel pe;
        pe.value = " ";
        pe.color = 5;
        wino.top().screen["diao"] =  vector<vector<pixel>> (3 , (vector<pixel> (x-9 , pe)));
        
        
    }
    if(wino.top().stl["cy"]==wino.top().vs["dialog"].size()){
        wino.pop();
        return;
    }
    if(wino.top().stl["cx"]==wino.top().vs["dialog"][wino.top().stl["cy"]].size()){
        if((k==" ")||(k=="Enter")){
            wino.top().stl["cx"]=0;
            wino.top().stl["cy"]++;
            wino.top().stl["tempx"]=0;
            wino.top().stl["tempy"]=0;
            pixel pe;
            pe.value = " ";
            pe.color = 5;
            wino.top().screen["diao"] =  vector<vector<pixel>> (3 , (vector<pixel> (x-9 , pe)));
        
        }
        return;
    }
    if(wino.top().stl["tempx"]==wino.top().screen["diao"][0].size()){
        wino.top().stl["tempx"]=0;
        wino.top().stl["tempy"]++;
    }
    if(wino.top().stl["tempy"]!=wino.top().screen["diao"].size()){
        pixel pe;
        pe.color = 5;
        pe.value = wino.top().vs["dialog"][wino.top().stl["cy"]][wino.top().stl["cx"]];
        wino.top().screen["diao"][wino.top().stl["tempy"]][wino.top().stl["tempx"]] = pe;
        wino.top().stl["tempx"]++; 
        if(!input::ikd(input::key::Shift))delay(15);
    }
    wino.top().stl["cx"]++;
    ita(wino.top().screen["dialog"] , wino.top().screen["diao"] , 9 , 1 , 1);
    ita(wino.top().screen["screen"] , wino.top().screen["dialog"] , 0 , y-5 , 0);   

}