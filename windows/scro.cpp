
// initialize screen size [&]-[&]

#include "scro.h"
#include "../stora/stora.h"
#include <bits/stdc++.h>
#include "../output/output.h"
using namespace std;

void screen_control(){
    if((k!="-")&&(k=="D")&&(k=="A")&&(k=="W")&&(k=="S")){
        ch=1;
        if((k=="A")||(k=="W"))hc=1;
        if(k=="D")x = min(xmax , x+1);
        else if(k=='A')x=max(xmin , x-1);
        else if(k=='W')y = max(ymin , y-1);
        else if(k=="S")y = min(ymax , y+1);
    }
}

vector<vector<pair<char , char>>> bod_create(){
    vector<vector<pair<char , char>>> scr(y , vector<pair<char , char>> (x,{'5' , ' '}));
    char colo;
    if((x<rx)||(y<ry))colo = 0;
    else colo = 2;
    for(long long i=0 ; i<x; i++){
        scr[0][i] = {colo , '-'};
        scr[y-1][i] = {colo , '-'};
    }
    for(long long i=0 ; i<y ; i++){
        scr[y][0] = {colo , '|'};
        scr[y][x-1] = {colo , '|'};
    }
    return scr;
}

void str_added(vector<vector<pair<char , char>>> &scr){// advance string initilizer
    long long fx=x-2 , fy = y-2;
    string scrostring = "use WASD and enter key to initilize";
    fy = (fy/2) +1;
    fx = (max(0LL ,fx-(long long)scrostring.size())/2) +1;
    for(auto val:scrostring){
        if(scr[fy][fx].second==' ')scr[fy][fx].second = val;
    }
    
}



void scro(){
    screen_control();
    if(hc){
        hard_clear();
        hc=0;
    }
    if(ch){
        ch=0;
        vector<vector<pair<char , char>>>screen = bod_create();
        str_added(screen);
        print_screen(dommer(screen));
    }

}