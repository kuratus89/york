
#include "error.h"
#include "../output/output.h"
#include "../stora/stora.h"
#include "window.h"
#include "../lib.h"

void error(){
    soft_clear();
    cout<<"sorry but the game crash >_<"<<endl;
    cout<<"reason => ";
    cout<<wino.top().sts["value"];

}

void crash(string s){
    win gw;
    gw.name = "error";
    gw.sts["value"] = s;
    wino.push(gw);
}