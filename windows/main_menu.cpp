
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"
#include "../physics/physics.h"

void menu_adder(char color){
    wino.top().screen["menu"]= vector<vector<pair<char , char>>> (10 , vector<pair<char , char>> (15 , {'5' , ' '}));
        
    vector<string> options= {
        " Single Player",
        " Multi Player",
        " Settings",
        " Quit"
    };
    long long jy = 0;
    for(long long i=0 ; i<options.size(); i++){
        if((jy>=wino.top().screen["menu"].size())||(jy<0))continue;
        long long jx=0;
        if(i==wino.top().stl["selecter"]){
            wino.top().screen["menu"][jy][jx]={color , '-'};
            jx++;
            wino.top().screen["menu"][jy][jx] = {color , '>'};
            jx++;
        }
        for(auto val:options[i]){
            if((jx>=wino.top().screen["menu"][0].size())||(jx<0))continue;
            wino.top().screen["menu"][jy][jx] = {color , val};
            jx++;
        }
        jy++;
    }

}

void inpt(){
    if(k=="W")wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"]=3;
    if(wino.top().stl["selecter"]==4)wino.top().stl["selecter"]=0;
    if((k=="W")||(k=="S"))menu_adder('5');
    
}


void main_menu(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        boot_data aalu ;
        if(!load_boot_data("data" , "boot.kp" , aalu)){
            win er;
            er.name = "error";
            er.sts["value"] = "unable to load the data";
            wino.push(er);
            return;
        }
        player = aalu.sts["character"][0];
        x = aalu.stl["x"];
        y = aalu.stl["y"];
        wino.top().screen["blank_screen"] = bod_create('5' , x , y);
        dialog_seprater('5' , wino.top().screen["blank_screen"]);
        wino.top().screen["screen"] = wino.top().screen["blank_screen"];
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["stage"]=1;
        wino.top().stl["xtar"]= x-22;
        // wino.top().stl["ytar"]=y-2;
        wino.top().stl["posd"]=0;  
        wino.top().stl["selecter"]=0;
        wino.top().stl["title_animation"]=0;
        wino.top().stl["player_animation"]=0;
        wino.top().stl["ty"]=-title.size();
        wino.top().stl["menu_animation"]=0;
        wino.top().screen["menu"]= vector<vector<pair<char , char>>> (10 , vector<pair<char , char>> (15 , {'5' , ' '}));
        wino.top().screen["platform"]= vector<vector<pair<char , char>>> (y , vector<pair<char , char>> (20 , {'5' , ' '}));
        wino.top().stl["mx"]=-wino.top().screen["menu"][0].size();
        menu_adder('5');
        for(auto &val:wino.top().screen["platform"])val[6] = {'5' , '#'};
        for(long long i=1 ;i<=11 ; i++)wino.top().screen["platform"][0][i]={'5' , '='};
        wino.top().screen["platform"][0][0]= {'5' , '<'};
        wino.top().screen["platform"][0][12] = {'5' , '>'};
        wino.top().stl["platform_visible"]=0;
    }
    // wino.top().screen[cy][cx] = {'5' , ' '};
    inpt();
    if(wino.top().stl["posd"]==0){
        wino.top().screen["screen"] = wino.top().screen["blank_screen"];
        delay(40);
        if(!isbo()){
            cy++;
        }
        else {
            if(wino.top().stl["xtar"]>cx){
                cx++;
            }
            else {
                wino.top().stl["posd"]++;
            }
        }
    }
    else if((wino.top().stl["posd"]==1)){
        wino.top().stl["platform_visible"]=1;
        delay(60);
        wino.top().screen["screen"] = wino.top().screen["blank_screen"];
        if(wino.top().stl["player_animation"]==0){
            cy--;
            if(cy == ((y-2)/2)+1)wino.top().stl["player_animation"]=1;
        }
        if(wino.top().stl["title_animation"]==0){
            wino.top().stl["ty"]++;
            if(wino.top().stl["ty"]==1)wino.top().stl["title_animation"]=1;
        }
        if(wino.top().stl["menu_animation"]==0){
            wino.top().stl["mx"]++;
            if(wino.top().stl["mx"]==4)wino.top().stl["menu_animation"]=1;
        }
        if((wino.top().stl["player_animation"]==1)&&(wino.top().stl["title_animation"]==1)&&(wino.top().stl["menu_animation"]))wino.top().stl["posd"]=2;
        
    }
    else if(wino.top().stl["posd"]==2){
        // cout<<"he";

    }
    // if(wino.top().stl["posd"]==1)
    if(wino.top().stl["platform_visible"]==1)par_scr(wino.top().screen["screen"] , wino.top().screen["platform"] , cx-6 , cy+1);
    par_scr(wino.top().screen["screen"] , wino.top().screen["menu"] , wino.top().stl["mx"] , ((y - wino.top().screen["menu"].size()-2)/2)+1);
    par_scr(wino.top().screen["screen"] , title ,((x-title[0].size()-2)/2)+1, wino.top().stl["ty"] );
    wino.top().screen["screen"][cy][cx] = {player_color , player};
    

}