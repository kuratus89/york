
#include "../../output/output.h"
#include "../window.h"
long long mx;
long long my;
int  colo;
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
        colo = wino.top().stl["color"];
        mx=0;
        my=ms.size()+2;
        for(auto &val:ms)mx = max(mx ,(long long) val.size());
        mx = max(mx , (long long)tit.size());
        mx+=2;
        wino.top().screen["screen"] = pre_screen;
        wino.top().screen["par_screen"] = bod_create(colo , mx , my );
        long long nx=1, ny=1;
        pixel pe;
        pe.color = colo;
        for(auto &val:ms){
            nx=1;
            for(auto &valo:val){
                pe.value = valo;
                wino.top().screen["par_screen"][ny][nx] = pe;
                nx++;
            }
            ny++;
        }
        nx = ((mx-2-tit.size())/2) +1;
        for(auto &val:tit){
            pe.value = val;
            wino.top().screen["par_screen"][0][nx]= pe;
            nx++;
        }

    }
    ita(wino.top().screen["screen"] , wino.top().screen["par_screen"] ,((max(0LL , x-mx)/2)+1),((max(0LL , y-my)/2)+1),1);
    inpu();
}