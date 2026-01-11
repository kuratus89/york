
#include "../window.h"
#include "../../output/output.h"

void opt_adder(){
    wino.top().screen["appreance"] = bod_create('5' , 30 , 10);
    vector<string> opt = {
      " EDIT CHARACTER",
      " EDIT CHARACTER COLOR",
      " DONE"  
    };
    long long hy=1;
    for(long long i=0 ; i<opt.size() ; i++){
        long long hx = 2;
        if(hy>=wino.top().screen["appreance"].size())continue; 
        if(i==wino.top().stl["selecter"]){
            wino.top().screen["appreance"][hy][hx]= {'5' , '-'};
            hx++;
            wino.top().screen["appreance"][hy][hx]= {'5' , '>'};
            hx++;
        }
        for(auto val:opt[i]){
            if(hx>=wino.top().screen["appreance"][0].size())continue;
            wino.top().screen["appreance"][hy][hx] ={'5' , val};
            hx++;
        }
        hy++;
    }
}

void inptt(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = 2;
    if(wino.top().stl["selecter"]==3)wino.top().stl["selecter"]=0;

    if(k=="Enter"){
        if(wino.top().stl["selecter"]==0){
            win ch;
            ch.name = "input_str";
            ch.sts["value"]="character";
            ch.sts["api"]="player_cha";
            ch.stl["limit"]=1;
            ch.stl["no_empty"]=1;
            wino.push(ch);            
        }
        else if(wino.top().stl["selecter"]==1){
            win cl;
            cl.name = "input_clr";
            cl.sts["api"]="pl_color";
            wino.push(cl);
        }
        else if(wino.top().stl["selecter"]==2){
            wino.pop();
        }
    }
}

void appearance(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle =1;
        wino.top().type=0;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"]=0;
    }
    if(wino.top().sts["pl_color"]!="")player_color = wino.top().sts["pl_color"][0];
    if(wino.top().sts["player_cha"]!="")player = wino.top().sts["player_cha"][0];
    opt_adder();
    par_scr(wino.top().screen["screen"] , wino.top().screen["appreance"] , ((x-wino.top().screen["appreance"][0].size()-2)/2)+1 , ((y-wino.top().screen["appreance"].size()-2)/2)+1);
    inptt();
}