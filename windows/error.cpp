
#include "error.h"
#include "../output/output.h"
#include "../stora/stora.h"
#include "window.h"
#include "../lib.h"

void error(){
    // soft_clear();
    hard_clear();
    cout<<"sorry but the game crash >_<"<<endl;
    cout<<"reason => ";
    cout<<wino.top().sts["value"];
}

void crash(string s){
    hard_clear();
    cout<<"sorry but the game crash >_<"<<endl;
    cout<<"reason => ";
    cout<<s<<endl;
    if(wino.size())cout<<"window => " + wino.top().name;
    exit(1);
}

// void crash(string s){
//     win gw;
//     gw.name = "error";
//     gw.sts["value"] = s;
//     gw.sts["value"]+= "\n window: "+ wino.top().name;
//     wino.push(gw);

// }