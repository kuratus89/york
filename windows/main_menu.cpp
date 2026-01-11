
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"
#include "../physics/physics.h"
#include "error.h"
void menu_adder(char color){
    wino.top().screen["menu"]= vector<vector<pair<char , char>>> (10 , vector<pair<char , char>> (16 , {'5' , ' '}));
        
    vector<string> options= {
        " Single Player",
        " Multi Player",
        " Appearance",
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
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"]=4;
    if(wino.top().stl["selecter"]==5)wino.top().stl["selecter"]=0;
    if((k=="W")||(k=="S"))menu_adder('5');
    if(k=="Enter"){
        if(wino.top().stl["animation"]!=-1)return;
        if(wino.top().stl["selecter"]==0){

        }
        else if(wino.top().stl["selecter"]==1){
            win message;
            message.name = "msg";
            message.sts["title"]= "umm";
            message.vs["msg"] = {
                "multiplayer has not been added yet",
                "if people like this game then i will add it in future"
            };
            message.sts["color"]="0";
            wino.push(message);
        }
        else if(wino.top().stl["selecter"]==2){
            wino.top().stl["animation"]=2;
        }
        else if(wino.top().stl["selecter"]==3){
            
        }
        else if(wino.top().stl["selecter"]==4){

        }
    }
    
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
        player_color = aalu.sts["player_color"][0];
        x = aalu.stl["x"];
        y = aalu.stl["y"];
        wino.top().screen["blank_screen"] = bod_create('5' , x , y);
        dialog_seprater('5' , wino.top().screen["blank_screen"]);
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["stage"]=1;
        wino.top().stl["xtar"]= x-22;
        wino.top().stl["animation"]=0;  
        wino.top().stl["selecter"]=0;
        wino.top().stl["title_animation"]=0;
        wino.top().stl["player_animation"]=0;
        wino.top().stl["ty"]=-title.size();
        wino.top().stl["menu_animation"]=0;
        wino.top().screen["menu"]= vector<vector<pair<char , char>>> (10 , vector<pair<char , char>> (16 , {'5' , ' '}));
        wino.top().screen["platform"]= vector<vector<pair<char , char>>> (y , vector<pair<char , char>> (30 , {'5' , ' '}));
        wino.top().stl["mx"]=-wino.top().screen["menu"][0].size();
        menu_adder('5');
        for(auto &val:wino.top().screen["platform"])val[6] = {'5' , '#'};
        wino.top().stl["apx"]=12;
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]={'5' , '='};
        wino.top().screen["platform"][0][0]= {'5' , '<'};
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = {'5' , '>'};
        wino.top().stl["platform_visible"]=0;
        wino.top().stl["fx"]= wino.top().stl["xtar"];
        wino.top().screen["player"] = {{{player_color , player}}};
    }
    wino.top().screen["screen"] = wino.top().screen["blank_screen"];
        
    
    // wino.top().screen[cy][cx] = {'5' , ' '};
    if(wino.top().stl["animation"]==0){
        delay(40);
        if(!isbo()){
            cy++;
        }
        else {
            if(wino.top().stl["xtar"]>cx){
                cx++;
            }
            else {
                wino.top().stl["animation"]++;
            }
        }
    }
    else if((wino.top().stl["animation"]==1)){
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
        if((wino.top().stl["player_animation"]==1)&&(wino.top().stl["title_animation"]==1)&&(wino.top().stl["menu_animation"]))wino.top().stl["animation"]=-1;
        
    }
    else if(wino.top().stl["animation"]==2){
        delay(50);
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]={'5' , '='};
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = {'5' , '>'};
        wino.top().stl["apx"]++;
        if(wino.top().stl["apx"]>=28)wino.top().stl["animation"]=3;
    }
    else if(wino.top().stl["animation"]==3){
        delay(50);
        cx++;
        if(cx>x)wino.top().stl["animation"]=4;
    }
    else if(wino.top().stl["animation"]==4){
        wino.top().stl["animation"]=5;
        win ap;
        ap.name="appearance";
        wino.push(ap);
        return;
    }
    else if(wino.top().stl["animation"]==5){
        boot_data aalu ;
        if(!load_boot_data("data" , "boot.kp" , aalu)){
            win er;
            er.name = "error";
            er.sts["value"] = "unable to load the data";
            wino.push(er);
            return;
        }
        aalu.sts["character"] = {player};
        aalu.sts["player_color"] = {player_color};
        if(!save_boot_data(aalu , "data" , "boot.kp")){
            win gw;
            gw.name = "error";
            gw.sts["value"] = "cannot save files";
            wino.push(gw);
        }
        wino.top().screen["player"] = {{{player_color , player}}};
        wino.top().stl["animation"]=6;
    }
    else if(wino.top().stl["animation"]==6){
        delay(50);
        cx--;
        if(cx==wino.top().stl["xtar"])wino.top().stl["animation"]=7;
    }
    else if(wino.top().stl["animation"]==7){
        delay(60);
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]={'5' , '='};
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = {'5' , '>'};
        wino.top().screen["platform"][0][wino.top().stl["apx"]+1]= {'5' , ' '};
        wino.top().stl["apx"]--;
        if(wino.top().stl["apx"]==12)wino.top().stl["animation"]=-1;
    }

    if(wino.top().stl["platform_visible"]==1)par_scr(wino.top().screen["screen"] , wino.top().screen["platform"] , wino.top().stl["xtar"]-6 , cy+1);
    par_scr(wino.top().screen["screen"] , wino.top().screen["menu"] , wino.top().stl["mx"] , ((y - wino.top().screen["menu"].size()-2)/2)+1);
    par_scr(wino.top().screen["screen"] , title ,((x-title[0].size()-2)/2)+1, wino.top().stl["ty"] );
    par_scr(wino.top().screen["screen"] , wino.top().screen["player"] , cx , cy);
    inpt();

}