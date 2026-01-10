#include "../window.h"
#include "../../output/output.h"
#include "../../stora/stora.h"

long long lim;
string s;
bool exito=0;
void incha(){
    if((k!="-")&&(k.size()==1)){
        if(s.size()<lim)s.push_back(k[0]);
    }
    if(k=="Backspace"){
        if(!s.empty())s.pop_back();
    }
    if(k=="Enter"){
        string val = wino.top().sts["api"];
        wino.pop();
        wino.top().sts[val] = s;
        exito=1;
    }
}
void str_adder(char colo){
    long long vx=1;
    for(auto val:s){
        if(vx>=40)break;
        wino.top().screen["par_screen"][1][vx]={colo,val};
        vx++;
    }
}
void clear_win(char colo){
    for(long long i=1 ; i<39 ; i++){
        wino.top().screen["par_screen"][1][i]={colo , ' '};
    }
}

void input_str(){
    
    auto &pora = wino.top();

    if(!pora.initilizzed){
        pora.initilizzed=1;
        pora.type=1;
        pora.screen["screen"] = pre_screen;
        pora.screen["par_screen"] = bod_create('5' ,40 ,3);
        pora.screen_handle=1;
        lim = pora.stl["limit"];
        string title = "ENTER ";
        title+=pora.sts["value"];
        exito=0;
        s="";
        long long hx = (max(0LL , 38 -(long long) title.size())/2)+1;
        for(auto val:title){
            if(hx>39)break;
            pora.screen["par_screen"][0][hx] = {'5' , val};
            hx++;
        }
    }
    incha();
    if(exito)return;
    clear_win('5');
    str_adder('5');
    par_scr(pora.screen["screen"] , pora.screen["par_screen"] , (((x-2-40)/2) +1) , (((y-2-4)/2) +1));
    
}