
#include "../../output/output.h"
#include "../window.h"
long long mx;
long long my;
char  colo;
void inpu(){
    if(k=="Enter"){
        wino.pop();
    }
}

void msg(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().type=1;
        wino.top().screen_handle=1;
        string tit =wino.top().sts["title"];
        vector<string> ms = wino.top().vs["msg"];
        colo = wino.top().sts["color"][0];
        mx=0;
        my=ms.size()+2;
        for(auto &val:ms)mx = max(mx ,(long long) val.size());
        mx = max(mx , (long long)tit.size());
        mx+=2;
        wino.top().screen["screen"] = pre_screen;
        wino.top().screen["par_screen"] = bod_create(colo , mx , my );
        long long nx=1, ny=1;
        for(auto &val:ms){
            nx=1;
            for(auto &valo:val){
                wino.top().screen["par_screen"][ny][nx] = {colo , valo};
                nx++;
            }
            ny++;
        }
        nx = ((mx-2-tit.size())/2) +1;
        for(auto &val:tit){
            wino.top().screen["par_screen"][0][nx]= {colo , val};
            nx++;
        }

    }
    par_scr(wino.top().screen["screen"] , wino.top().screen["par_screen"] ,((max(0LL , x-mx)/2)+1),((max(0LL , y-my)/2)+1) );
    inpu();
}