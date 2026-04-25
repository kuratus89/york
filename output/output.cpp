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

// string dommer(vector<vector<pair<char , char>>> &screen){// dommer process the screen data to string :)
//     string s;
//     for(auto vol:screen){
//         for(auto val:vol){
//             string colo = in_to_color[val.first -'0'];
//             for(auto hulululu:colo)s.push_back(hulululu);
//             s.push_back(val.second);
//         }
//         s.push_back('\n');
//     }
//     return s;
// }

void print_screen(string screen){// output the string with soft clear *-*
    soft_clear();
    cout<<screen;
}

void text_adder(vector<vector<pixel>> &screen , int x , int y , string s , int color){
    if(x == INT_MIN)x = max(0 ,(int) (screen[0].size() - s.size())/2);
    if(y == INT_MIN)y = screen.size()/2;
    if(y<0)return;
    for(auto val:s){
        if(x<0)continue;
        pixel pe;
        pe.color = color;
        pe.value = val;
        screen[y][x] = pe;
        x++;
    }
}

vector<vector<pixel>> bod_create(int colo , long long lx , long long ly  ){ 
    pixel pe;
    pe.color=colo;
    pe.value = " ";
    vector<vector<pixel>> scr(ly , vector<pixel> (lx,pe));
    pe.value = "─";
    for(long long i=0 ; i<lx; i++){
        scr[0][i] =pe;
        scr[ly-1][i] = pe;
    }
    pe.value = "|";
    for(long long i=0 ; i<ly ; i++){
        scr[i][0] = pe;
        scr[i][lx-1] = pe;
    }
    // for(long long i=y-4 ; i<y-1 ; i++){
    //     scr[i][8] ={colo ,'|'};
    // }
    pe.value="╭";
    scr[0][0]       = pe;
    pe.value = "╯";
    scr[ly-1][lx-1] = pe;
    pe.value = "╮";
    scr[0][lx-1]    = pe;
    pe.value = "╰";
    scr[ly-1][0]    = pe;

    return scr;
}
void dialog_seprater(char colo , vector<vector<pair<char , char>>> &scro){
    for(long long i=1; i<x-1; i++)scro[y-5][i] = {colo , '-'};
}

void dialog_adder(vector<vector<pixel>> &scro , string name , char player_icon , string msg , int colo){
    pixel pe;
    pe.color = colo;
    pe.value = " ";
    for(long long i=y-4;i<y-1 ; i++){
        for(long long j=1 ; j<x-1 ; j++){
            scro[i][j] = pe;
        }
    }
    pe.value = "─";
    for(long long i=1 ; i<x-1; i++)scro[y-5][i] =pe;
    pe.value = "|";
    for(long long i=y-4 ; i<y-1 ; i++)scro[i][8] =pe;
    pe.color = player_color;  
    pe.value = string(1 , player_icon);
    scro[y-4][4]=pe;
    long long nx= (max(0LL,(7-(long long)name.size()))+1);
    long long ny=y-3;
    pe.color = colo;
    for(auto val:name){
        if(scro[ny][nx].value!=" "){
            ovr("dialog name");
            return;
        }
        pe.value = val;
        scro[ny][nx]=pe;
        nx++;
        if(nx>7){
            nx = 2;
            ny++;
        }
    }
    nx = 10;
    ny = y-4;
    for(auto val:msg){
        if(scro[ny][nx].value!=" "){
            ovr("dialog");
            return;
        }
        pe.value = val;
        scro[ny][nx]=pe;
        nx++;
        if(nx>x-3){
            nx = 10;
            ny++;
        }
    }

}


// void kuramizer(vector<vector<pair<char, char>>> &screen){
//     if(pre_screen==screen)return;
//     pre_screen = screen;
//     print_screen(dommer(screen));
// }
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
void par_scr(vector<vector<pair<char, char>>> &screen,vector<vector<pair<char, char>>> &par,long long vx, long long vy) {
    for (long long sy = 0; sy < (long long)par.size(); ++sy) {
        long long ty = vy + sy;
        if (ty <= 0 || ty >= y-1) continue;
        for (long long sx = 0; sx < (long long)par[sy].size(); ++sx) {
            long long tx = vx + sx;
            if (tx <= 0 || tx >= x-1) continue;
            screen[ty][tx] = par[sy][sx];
        }
    }
}

void ita(vector<vector<pixel>> &screen ,vector<vector<pixel>> &par , int vx , int vy , bool boder){
    if((par.empty())||(screen.empty())||(par[0].empty())||(screen[0].empty()))return;

    if(vx == INT_MIN)vx = (((int) screen[0].size() - (int)par[0].size()- 2)/2)+1;
    if(vy == INT_MIN)vy = (((int) screen.size() - (int) par.size() - 2)/2)+1;

    for(int sy = 0 ; sy< (int)par.size() ; sy++){
        int ty = vy+sy;
        if((boder)&&((ty <=0)||(ty>= y-1)))continue;
        for(int sx = 0 ; sx<(int)par[sy].size() ; sx++){
            int tx = vx+sx;
            if((boder)&&(tx <=0)|| (tx>=x-1))continue;
            if((ty<0)||(ty>=(int)screen.size()))continue;
            screen[ty][tx]= par[sy][sx];
        }
    }
}




void option_adder(vector<vector<pixel>> &screen , vector<string> &options , long long selecter , long long sx , long long sy , bool boder){

    if(sx<=0){
        int ma = 0;
        for(auto val:options)ma = max(ma , (int)val.size());
        sx = ma+5;
    }
    if(sy<=0){
        sy = options.size()+3;
    }

    if(boder)screen = bod_create(5 , sx ,sy);
    else{
        pixel pe;
        pe.color = 5;
        pe.value = " ";
        screen = vector<vector<pixel>> (sy , vector<pixel> (sx ,  pe));
    }
    pixel pe;
    pe.color = 5;
    long long hy=1;
    for(long long i=0 ; i<options.size() ; i++){
        long long hx = 2;
        if(hy>=screen.size())continue; 
        if(i==wino.top().stl["selecter"]){
            pe.value = "─";
            screen[hy][hx]= pe;
            hx++;
            pe.value = ">";
            screen[hy][hx]= pe;
            hx++;
        }
        for(auto val:options[i]){
            if(hx>=screen[0].size())continue;
            pe.value = val;
            screen[hy][hx] =pe;
            hx++;
        }
        hy++;
    }
}

string dommer(vector<vector<pixel>> &scr){
    string s;
    for(auto &var:scr){
        for(auto &val:var){
            s+= in_to_color[val.color];
            s+=val.value;
        }
        s+="\n";
    }
    return s;
}

void kuramizer(vector<vector<pixel>> &screen){
    if(pre_screen==screen)return;
    pre_screen = screen;
    print_screen(dommer(screen));
}

void fad(vector<vector<pixel>> &screen , bool &fps , bool &latency , double &ms){
    long long j =0;
    long long i=0;
    string f,l;
    if(fps){
        j++;
        f = to_string((long long)(1000.0/ms));
    }
    if(latency){
        j++;
        l = to_string((long long)ms);
    }
    if(j==0)return;
    i = max(l.size()+10 , f.size()+6);
    pixel px;
    px.value = " ";
    px.color = 5;
    screen = vector<vector<pixel>> (j , vector<pixel> (i , px));
    long long jy =0;
    long long jx=0;
    if(fps){
        for(auto val:"fps: "){
            screen[jy][jx].value = val;
            jx++;
        }
        for(auto val:f){
            screen[jy][jx].value = val;
            jx++;
        }
        jy++;
    }
    jx=0;
    if(latency){
        for(auto val:"latency: "){
            screen[jy][jx].value = val;
            jx++;
        }
        for(auto val:l){
            screen[jy][jx].value = val;
            jx++;
        }
    }
}

void  vertical_window_align(vector<vector<pixel>> &result , vector<vector<pixel>> &top , vector<vector<pixel>> &bottom , bool center_align){
    if((top.size()<=0)||(bottom.size()<=0))return;
    int x=max(top[0].size() , bottom[0].size());
    int y = top.size() + bottom.size();

    pixel pe;
    pe.color = 5;
    pe.value = " ";
    result = vector<vector<pixel>> (y , vector<pixel> (x , pe));
    
    if(center_align)ita(result , top , INT_MIN , 0 , 0);
    else ita(result , top , 0 , 0 , 0);

    if(center_align)ita(result , bottom , INT_MIN, top.size(),0);
    else ita(result , bottom , 0 , top.size() , 0);
}

void horizontal_window_align(vector<vector<pixel>> &result ,vector<vector<pixel>> &left , vector<vector<pixel>> &right , bool center_align){
    int lx = left[0].size();
    int rx = right[0].size();
    int x = lx +rx;
    int y = max(left.size() , right.size());

    pixel pe;
    pe.color = 5;
    pe.value = " ";

    result  = vector<vector<pixel>> (y , vector<pixel> (x , pe));

    if(center_align)ita(result , left , 0 , INT_MIN, 0);
    else ita(result , left , 0 ,0  , 0);

    if(center_align)ita(result , right , lx , INT_MIN , 0);
    else ita(result , right , lx , 0 , 0);

}

void text_to_win_xlim(vector<vector<pixel>> &win , string s , int x){
    if(x<=0)x = s.size();
    int i=0;
    win.clear();
    vector<pixel> pv;
    pixel pe;
    pe.color = 5;
    for(auto val:s){
        if(i==x){
            win.push_back(pv);
            pv.clear();
            i=0;
        }
        pe.value = val;
        pv.push_back(pe);
    }
    if(pv.size())win.push_back(pv);
}

void bod_add(vector<vector<pixel>> &result , vector<vector<pixel>> &scr){
    if(scr.size()==0)return;
    result = bod_create(5 , scr[0].size()+2 , scr.size()+2);
    ita(result , scr , 1 , 1 , 0);
}