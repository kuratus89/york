#include "../window.h"
#include "../../output/output.h"

void clor(){
    wino.top().screen["clr"] = bod_create('5' , 15 , 8);
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
    for(long long i=0 ; i<color.size() ; i++){
        long long hx = 2;
        if(hy>=wino.top().screen["clr"].size())continue; 
        if(i==wino.top().stl["selecter"]){
            wino.top().screen["clr"][hy][hx]= {'0'+i, '-'};
            hx++;
            wino.top().screen["clr"][hy][hx]= {'0'+ i , '>'};
            hx++;
        }
        for(auto val:color[i]){
            if(hx>=wino.top().screen["clr"][0].size())continue;
            wino.top().screen["clr"][hy][hx] ={'0' +i , val};
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
        char vb = '0' + wino.top().stl["selecter"];
        s.push_back(vb);
        wino.pop();
        wino.top().sts[key] = s;
        
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
    par_scr(wino.top().screen["screen"] , wino.top().screen["clr"] , ((x-wino.top().screen["clr"][0].size()-2)/2)+1 , ((y-wino.top().screen["clr"].size()-2)/2)+1);
    inppt();
}