
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"
#include "../physics/physics.h"
#include "error.h"
long long which_title = 0;
void menu_adder(int color){
    pixel pe;
    pe.color = color;
    pe.value = " ";
    wino.top().screen["menu"]= vector<vector<pixel>> (10 , vector<pixel> (16 , pe));
        
    vector<string> options= {
        " New Game",
        " Load Game",
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
            pe.value = "─";
            wino.top().screen["menu"][jy][jx]=pe;
            jx++;
            pe.value = ">";
            wino.top().screen["menu"][jy][jx] = pe;
            jx++;
        }
        for(auto val:options[i]){
            if((jx>=wino.top().screen["menu"][0].size())||(jx<0))continue;
            pe.value = val;
            wino.top().screen["menu"][jy][jx] = pe;
            jx++;
        }
        jy++;
    }

}

void inpt(){
    if(k=="W")wino.top().stl["selecter"]--;
    else if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"]=5;
    if(wino.top().stl["selecter"]==6)wino.top().stl["selecter"]=0;
    if((k=="W")||(k=="S"))menu_adder(5);
    if(k=="Enter"){
        if(wino.top().stl["animation"]!=-1)return;
        if(wino.top().stl["selecter"]==0){
            win gm;
            gm.name = "start_new_game";
            wino.push(gm);
        }
        if(wino.top().stl["selecter"]==1){
            win lg;
            lg.name = "load_world";
            wino.push(lg);
        }
        else if(wino.top().stl["selecter"]==2){
            win message;
            message.name = "msg";
            message.sts["title"]= "umm";
            message.vs["msg"] = {
                "multiplayer has not been added yet",
                "if people like this game then i will add it in future"
            };
            message.stl["color"]=0;
            wino.push(message);
        }
        else if(wino.top().stl["selecter"]==3){
            wino.top().stl["animation"]=2;
        }
        else if(wino.top().stl["selecter"]==4){
            win st;
            st.name = "settings";
            wino.push(st);
            return;
        }
        else if(wino.top().stl["selecter"]==5){
            gameon=0;
        }
    }
    
}

void dialo(){
    wino.top().screen["dia"] = bod_create(5 , x , 5);
    wino.top().screen["dia"][0][0].value = "├";
    wino.top().screen["dia"][0][x-1].value = "┤"; 
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
        player_name =aalu.sts["name"]; 
        player = aalu.sts["character"][0];
        player_color = aalu.stl["player_color"];
        wino.top().screen["blank_screen"] = bod_create(5 , x , y);
        // dialog_seprater('5' , wino.top().screen["blank_screen"]);
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["stage"]=1;
        wino.top().stl["xtar"]= x-22;
        wino.top().stl["animation"]=0;  
        wino.top().stl["selecter"]=0;
        wino.top().stl["title_animation"]=0;
        wino.top().stl["player_animation"]=0;
        wino.top().stl["ty"]=-titles[which_title].size();
        wino.top().stl["menu_animation"]=0;
        pixel pe;
        pe.color = 5;
        pe.value = " ";
        wino.top().screen["menu"]= vector<vector<pixel>> (10 , vector<pixel> (16 , pe));
        wino.top().screen["platform"]= vector<vector<pixel>> (y , vector<pixel> (30 ,pe));
        wino.top().stl["mx"]=-wino.top().screen["menu"][0].size();
        menu_adder(5);
        // pe.value = "█";
        // for(auto &val:wino.top().screen["platform"])val[6] =pe;
        // for(auto &val:wino.top().screen["platform"])val[5] =pe;
        // for(auto &val:wino.top().screen["platform"])val[7] =pe;
        wino.top().stl["apx"]=12;
        pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]=pe;
        pe.value = "╭";
        wino.top().screen["platform"][0][0]= pe;
        pe.value = "╮";
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = pe;


        pe.value = "█";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][1][i]=pe;
        pe.value = "│";
        wino.top().screen["platform"][1][0]= pe;
        pe.value = "│";
        wino.top().screen["platform"][1][wino.top().stl["apx"]] = pe;


         pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][2][i]=pe;
        pe.value = "╰";
        wino.top().screen["platform"][2][0]= pe;
        pe.value = "╯";
        wino.top().screen["platform"][2][wino.top().stl["apx"]] = pe;



        wino.top().stl["platform_visible"]=0;
        wino.top().stl["fx"]= wino.top().stl["xtar"];
        pe.color = player_color;
        pe.value = string(1 , player);
        wino.top().screen["player"] = {{pe}};
        // cout << "titles[0].size() = " << titles[0].size() << endl;
        // cout << "titles[0][0].size() = " << titles[0][0].size() << endl;
        dialo();

    }
    wino.top().screen["screen"] = wino.top().screen["blank_screen"];
        
    
    // wino.top().screen[cy][cx] = {'5' , ' '};
    if(wino.top().stl["animation"]==0){
        delay(20);
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
        pixel pe;
        pe.color =5;
        pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]=pe;
        pe.value = "╭";
        wino.top().screen["platform"][0][0]= pe;
        pe.value = "╮";
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = pe;


        pe.value = "█";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][1][i]=pe;
        pe.value = "│";
        wino.top().screen["platform"][1][0]= pe;
        pe.value = "│";
        wino.top().screen["platform"][1][wino.top().stl["apx"]] = pe;


        pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][2][i]=pe;
        pe.value = "╰";
        wino.top().screen["platform"][2][0]= pe;
        pe.value = "╯";
        wino.top().screen["platform"][2][wino.top().stl["apx"]] = pe;
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
        aalu.sts["character"] = player;
        aalu.stl["player_color"]=player_color;
        if(!save_boot_data(aalu , "data" , "boot.kp")){
            win gw;
            gw.name = "error";
            gw.sts["value"] = "cannot save files";
            wino.push(gw);
        }
        pixel pe;
        pe.color = player_color;
        pe.value = string(1 ,player);
        wino.top().screen["player"] = {{pe}};
        wino.top().stl["animation"]=6;
    }
    else if(wino.top().stl["animation"]==6){
        delay(50);
        cx--;
        if(cx==wino.top().stl["xtar"])wino.top().stl["animation"]=7;
    }
    else if(wino.top().stl["animation"]==7){
        delay(60);
        pixel pe;
        pe.color = 5;
        pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][0][i]=pe;
        pe.value = "╭";
        wino.top().screen["platform"][0][0]= pe;
        pe.value = "╮";
        wino.top().screen["platform"][0][wino.top().stl["apx"]] = pe;


        pe.value = "█";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][1][i]=pe;
        pe.value = "│";
        wino.top().screen["platform"][1][0]= pe;
        pe.value = "│";
        wino.top().screen["platform"][1][wino.top().stl["apx"]] = pe;


        pe.value = "─";
        for(long long i=1 ;i<wino.top().stl["apx"] ; i++)wino.top().screen["platform"][2][i]=pe;
        pe.value = "╰";
        wino.top().screen["platform"][2][0]= pe;
        pe.value = "╯";
        wino.top().screen["platform"][2][wino.top().stl["apx"]] = pe;
        pe.value = " ";
        wino.top().screen["platform"][2][wino.top().stl["apx"]+1] = pe;
        wino.top().screen["platform"][1][wino.top().stl["apx"]+1] = pe;
        wino.top().screen["platform"][0][wino.top().stl["apx"]+1] = pe;
        wino.top().stl["apx"]--;
        if(wino.top().stl["apx"]==12)wino.top().stl["animation"]=-1;
    }

    if(wino.top().stl["platform_visible"]==1)ita(wino.top().screen["screen"] , wino.top().screen["platform"] , wino.top().stl["xtar"]-6 , cy+1,1);
    ita(wino.top().screen["screen"] , wino.top().screen["menu"] , wino.top().stl["mx"] , ((y - wino.top().screen["menu"].size()-2)/2)+1,1);
    ita(wino.top().screen["screen"] , titles[which_title] ,((x-titles[which_title][0].size()-2)/2)+1, wino.top().stl["ty"],1 );
    ita(wino.top().screen["screen"] , wino.top().screen["player"] , cx , cy ,1);
    ita(wino.top().screen["screen"] , wino.top().screen["dia"] , 0 , y-5 , 1);

    inpt();

}