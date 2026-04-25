#include "../window.h"
#include "../error.h"
#include "../../output/output.h"

void inopy(){
    if(k=="-")return;
    if(k=="W")wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;

    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = wino.top().vs["opt"].size()-1;
    else if(wino.top().stl["selecter"]==wino.top().vs["opt"].size())wino.top().stl["selecter"] = 0;

    if(k=="Enter"){
        string s;
        s = wino.top().vs["opt"][wino.top().stl["selecter"]];
        string api;
        api = wino.top().sts["api"];
        wino.pop();
        wino.top().sts[api] = s;
    }
}

void yan(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed = 1;
        wino.top().screen_handle = 1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"] = 0;
        if(!wino.top().vs.count("opt"))crash("options not provided for yan");
        if(!wino.top().sts.count("api"))crash("api not provided for yan");
        if(!wino.top().vs["opt"].size())crash("invalid options provided for yan");
        int lx=1;
        for(auto val:wino.top().vs["opt"])lx = max(lx , (int) val.size());
        if(wino.top().sts.count("desc"))text_to_win_xlim(wino.top().screen["desc"] , wino.top().sts["desc"] , lx+2);
        
        
        
    }
    option_adder(wino.top().screen["opt"] , wino.top().vs["opt"] , wino.top().stl["selecter"] , INT_MIN , INT_MIN, 0);
    if(wino.top().sts.count("desc"))vertical_window_align(wino.top().screen["main"] , wino.top().screen["desc"] , wino.top().screen["opt"] , 1);
    else wino.top().screen["main"] = wino.top().screen["opt"];
    bod_add(wino.top().screen["main_bod"] , wino.top().screen["main"]);
    ita(wino.top().screen["screen"] , wino.top().screen["main_bod"] , INT_MIN , INT_MIN , 0);
    inopy();
}