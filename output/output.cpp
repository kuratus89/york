#include "../lib.h"
#include "output.h"
#include "clear_screen.h"
#include "../stora/stora.h"
#include "../windows/window.h"


void ovr(string vallo){
    win over;
    over.name = "error";
    over.sts["value"] = "no space to print ->"+ vallo;
    while(!wino.empty())wino.pop();
    wino.push(over);
    hc=1;
}

string paint(string s ,string col ){//paint string with color
    s = string_to_color[col] + s + string_to_color["white"];
    return s;
}

string dommer(vector<vector<pair<char , char>>> &screen){// dommer process the screen data to string :)
    string s;
    for(auto vol:screen){
        for(auto val:vol){
            string colo = in_to_color[val.first -'0'];
            for(auto hulululu:colo)s.push_back(hulululu);
            s.push_back(val.second);
        }
        s.push_back('\n');
    }
    cout<<string_to_color["white"];
    return s;
}

void print_screen(string screen){// output the string with soft clear
    soft_clear();
    cout<<screen;
}

vector<vector<pair<char , char>>> bod_create(char colo , long long lx , long long ly  ){ // create boders of color colo
    vector<vector<pair<char , char>>> scr(ly , vector<pair<char , char>> (lx,{colo , ' '}));
    for(long long i=0 ; i<lx; i++){
        scr[0][i] = {colo , '-'};
        scr[ly-1][i] = {colo , '-'};
    }
    for(long long i=0 ; i<ly ; i++){
        scr[i][0] = {colo , '|'};
        scr[i][lx-1] = {colo , '|'};
    }
    // for(long long i=y-4 ; i<y-1 ; i++){
    //     scr[i][8] ={colo ,'|'};
    // }
    return scr;
}
void dialog_seprater(char colo , vector<vector<pair<char , char>>> &scro){
    for(long long i=1; i<x-1; i++)scro[y-5][i] = {colo , '-'};
}

void dialog_adder(vector<vector<pair<char , char>>> &scro , string name , char player_icon , string msg , char colo){
    for(long long i=y-4 ; i<y-1 ; i++){
        for(long long j=1 ; j<x-1 ; j++){
            scro[i][j] = {colo , ' '};
        }
    }
    for(long long i=1 ; i<x-1; i++)scro[y-5][i] = {colo , '-'};

    for(long long i=y-4 ; i<y-1 ; i++){
        scro[i][8] ={colo ,'|'};
    }
    scro[y-4][4]={colo , player_icon};
    long long nx= (max(0LL,(7-(long long)name.size()))+1);
    long long ny=y-3;
    for(auto val:name){
        if(scro[ny][nx].second!=' '){
            ovr("dialog name");
            return;
        }
        scro[ny][nx]={colo , val};
        nx++;
        if(nx>7){
            nx = 2;
            ny++;
        }
    }
    nx = 10;
    ny = y-4;
    for(auto val:msg){
        if(scro[ny][nx].second!=' '){
            ovr("dialog");
            return;
        }
        scro[ny][nx]={colo , val};
        nx++;
        if(nx>x-3){
            nx = 10;
            ny++;
        }
    }

}


void kuramizer(vector<vector<pair<char, char>>> &screen){
    if(pre_screen==screen)return;
    pre_screen = screen;
    print_screen(dommer(screen));
}
// void par_scr(vector<vector<pair<char, char>>> &screen,vector<vector<pair<char, char>>> &par , long long vx , long long vy){
//     long long tx=vx;
//     for(auto gl:par){
        
//         if((vy>=1)&&(vy<y-1)){
//             for(auto va:gl){
//                 if((vx>=1)&&(vx<x-1)){
//                     screen[vy][tx]=va;
//                 }
//                 tx++;
//             }
//         }
//         tx=vx;
//         vy++;
//     }    
// }
void par_scr(vector<vector<pair<char, char>>> &screen,
             vector<vector<pair<char, char>>> &par,
             long long vx, long long vy) {
    for (long long sy = 0; sy < (long long)par.size(); ++sy) {
        long long ty = vy + sy;
        if (ty <= 0 || ty >= y-5) continue;
        for (long long sx = 0; sx < (long long)par[sy].size(); ++sx) {
            long long tx = vx + sx;
            if (tx <= 0 || tx >= x) continue;
            screen[ty][tx] = par[sy][sx];
        }
    }
}



