#include "../window.h"
#include "../../output/output.h"

void clor(){
    wino.top().screen["clr"] = bod_create(5 , 15 , 8);
    // wino.top().screen["clr"] = vector<vector<pair<char , char>>> (8 , vector<pair<char , char>> (10  , {'5' , ' '}));
    vector<string> color = {
        " Red",
        " Blue",
        " Green",
        " Purple",
        " Cyan",
        " White"
    };
    long long hy=1;
    pixel pe;
    for(long long i=0 ; i<color.size() ; i++){
        long long hx = 2;
        pe.color = i;
        if(hy>=wino.top().screen["clr"].size())continue; 
        if(i==wino.top().stl["selecter"]){
            
            pe.value = "─";
            wino.top().screen["clr"][hy][hx]= pe;
            hx++;
            pe.value = ">";
            wino.top().screen["clr"][hy][hx]=pe;
            hx++;
        }
        for(auto val:color[i]){
            if(hx>=wino.top().screen["clr"][0].size())break;
            pe.value = string(1, val);
            wino.top().screen["clr"][hy][hx] =pe;
            hx++;
        }
        hy++;
    }
}
void inppt(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = 5;
    if(wino.top().stl["selecter"]==6)wino.top().stl["selecter"]=0;
    if(k=="Enter"){
        string s;
        string key = wino.top().sts["api"];
        int vb =wino.top().stl["selecter"];
        s.push_back(vb);
        wino.pop();
        wino.top().stl[key] =vb;
        
    }
}

void input_clr(){
        if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle =1;
        wino.top().type=0;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"] = 0;
    }
    clor();
    ita(wino.top().screen["screen"] , wino.top().screen["clr"] , ((x-wino.top().screen["clr"][0].size()-2)/2)+1 , ((y-wino.top().screen["clr"].size()-2)/2)+1);
    inppt();
}