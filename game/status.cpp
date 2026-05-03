#include "../output/output.h"
#include "../windows/window.h"
#include "../stora/stora.h"
#include "chunk.h"
#include "../windows/dynamic/inventory.h"
#include "weapon.h"
#include "../physics/physics.h"



void status(){

    if(wino.top().stl["status_initilize"]!=1){
       wino.top().stl["status_initilize"]=1;
       wino.top().screen["status"] = bod_create(5 , x, 5);
       wino.top().screen["item"] = bod_create(5 , 4,3);
       text_to_win_xlim(wino.top().screen["player"] , string(1 , player) , INT_MIN);
       text_to_win_xlim(wino.top().screen["name"] , player_name , INT_MIN);
       text_to_win_xlim(wino.top().screen["blank"] , " " , INT_MIN);
       text_to_win_xlim(wino.top().screen["divider"] , "|||" , 1);
       text_to_win_xlim(wino.top().screen["health"] , "Health:" , INT_MIN);
       text_to_win_xlim(wino.top().screen["item_text"] , "Item:" , INT_MIN);
       text_to_win_xlim(wino.top().screen["break"] , "Break:" , INT_MIN);
       text_to_win_xlim(wino.top().screen["weapon"] , "Weapon:" , INT_MIN);
       text_to_win_xlim(wino.top().screen["cordinate"] , "Cordinate:" , INT_MIN);

       vertical_window_align(wino.top().screen["prs"] , wino.top().screen["player"] , wino.top().screen["name"] , 1 , 0);
       vertical_window_align(wino.top().screen["profile_without_div"] , wino.top().screen["prs"] , wino.top().screen["blank"] , 1, 0);
       horizontal_window_align(wino.top().screen["profile"] , wino.top().screen["profile_without_div"] , wino.top().screen["divider"] , 1 , 0);
       wino.top().stl["health"] = -1;
       wino.top().stl["item"] = -1;
       wino.top().stl["break"] = -1;
       wino.top().sts["weapon"] = "";
       wino.top().stl["cor_update"]=1;
       wino.top().stl["update"] = 1;
    }
    if(wino.top().stl["health"]!=ear.health){
        wino.top().stl["health"] = ear.health;
        wino.top().stl["update"] = 1;
        wino.top().stl["health_update"]=1;
        wino.top().screen["health_bar"] = bod_create(5 , 12 , 3 );
        pixel pe;
        if(((float)ear.health/(float)max_health)>0.6f)pe.color = 2;
        else if(((float)ear.health/(float)max_health)>0.35f)pe.color = 1;
        else pe.color = 0;
        pe.value = "█";
        for(int i=1 ; i<=(((float)ear.health)/(float)max_health)*10 ; i++)wino.top().screen["health_bar"][1][i] = pe;
    }
    if(wino.top().stl["item"]!=selected_item){
        wino.top().stl["item"]=selected_item;
        wino.top().stl["update"]=1;
        wino.top().stl["item_update"]=1;
        pixel pe;
        pe.color = blocker[selected_item].second.second;
        pe.value = blocker[selected_item].second.first;

        wino.top().screen["item"][1][1] = pe;
        wino.top().screen["item"][1][2] = pe;
    }
    if(wino.top().stl["break"]!=break_block){
        wino.top().stl["break"] = break_block;
        wino.top().stl["update"] = 1;
        wino.top().stl["break_update"]=1;
        wino.top().screen["break_bar"] = bod_create(5 , 12 , 3);
        pixel pe;
        pe.color = 5;
        pe.value = "█";
        if(max_break_block!=0)for(int i=1 ; (i<=((break_block*10)/max_break_block)&&(i<=10)) ; i++)wino.top().screen["break_bar"][1][i] = pe;
    }
    if(wino.top().sts["weapon"]!=selected_weapon){
        wino.top().sts["weapon"] = selected_weapon;
        wino.top().stl["update"] = 1;
        wino.top().stl["weapon_update"]=1;
        text_to_win_xlim(wino.top().screen["weapon_name"] , selected_weapon , INT_MIN);
    }
    if((wino.top().stl["cor_update"])||(wino.top().stl["x"]!=cx)||(wino.top().stl["y"]!=cy)){
        wino.top().stl["x"] = cx;
        wino.top().stl["y"] = cy;
        wino.top().stl["cor_update"]=0;
        wino.top().stl["update"] = 1;
        text_to_win_xlim(wino.top().screen["cor"] , to_string(cx)+", " + to_string(cy) , INT_MIN);
        horizontal_window_align(wino.top().screen["cordinate_pack"] ,wino.top().screen["cordinate"] , wino.top().screen["cor"] , 1 , 0 );
        
    }
    if(show_fps||show_latency){
        if(wino.top().stl["seconds"] - seconds <1)return;
        wino.top().stl["update"]=1;
        wino.top().stl["fl"]=1;
        if(show_fps&&show_latency){
            text_to_win_xlim(wino.top().screen["fps"] , "Fps : " + to_string((int)(1000.0/ms)) , INT_MIN);
            text_to_win_xlim(wino.top().screen["latency"] , "Latency : " + to_string((int)ms) , INT_MIN);
            vertical_window_align(wino.top().screen["fl"] , wino.top().screen["fps"] , wino.top().screen["latency"] , 0 , 1);
        }
        else{
            if(show_fps)text_to_win_xlim(wino.top().screen["fl"] , "Fps : " + to_string((int)(1000.0/ms)) , INT_MIN);
            else text_to_win_xlim(wino.top().screen["fl"] , "Latency : " + to_string((int)ms) , INT_MIN);
        }
    }
    if(wino.top().stl["update"]){
        wino.top().stl["update"]=0;
        
        if(wino.top().stl["health_update"])horizontal_window_align(wino.top().screen["health_pack"] , wino.top().screen["health"] , wino.top().screen["health_bar"] , 1 , 0);

        if(wino.top().stl["item_update"])horizontal_window_align(wino.top().screen["item_pack"] , wino.top().screen["item_text"] , wino.top().screen["item"] , 1 , 0);

        if(wino.top().stl["break_update"])horizontal_window_align(wino.top().screen["break_pack"] , wino.top().screen["break"] , wino.top().screen["break_bar"]  , 1 , 0);

        if(wino.top().stl["weapon_update"])horizontal_window_align(wino.top().screen["weapon_pack"]  , wino.top().screen["weapon"] , wino.top().screen["weapon_name"] , 1 , 0);


  
        if((wino.top().stl["health_update"])||(wino.top().stl["item_update"]))horizontal_window_align(wino.top().screen["health_item"] , wino.top().screen["health_pack"] , wino.top().screen["item_pack"] , 1 , 1);

        if((wino.top().stl["break_update"])||(wino.top().stl["weapon_update"]))horizontal_window_align(wino.top().screen["break_weapon"] , wino.top().screen["break_pack"] , wino.top().screen["weapon_pack"] , 1 , 1);


        horizontal_window_align(wino.top().screen["stats"] , wino.top().screen["health_item"] , wino.top().screen["break_weapon"] , 1 , 0);

        horizontal_window_align(wino.top().screen["pro_stats"] , wino.top().screen["profile"] , wino.top().screen["stats"] , 1 , 0);

        horizontal_window_align(wino.top().screen["sta"] , wino.top().screen["pro_stats"] , wino.top().screen["cordinate_pack"] , 1 , 1);
        wino.top().screen["status"] = bod_create(5 , x-1 , 5);
        if(show_fps||show_latency){
            horizontal_window_align(wino.top().screen["pcf"] , wino.top().screen["sta"] , wino.top().screen["fl"] , 1 , 0 );
            ita(wino.top().screen["status"] , wino.top().screen["pcf"] , 1 , 1 , 0);
        }
        else ita(wino.top().screen["status"] , wino.top().screen["sta"] , 1 , 1, 0);

        wino.top().stl["health_update"] = wino.top().stl["item_update"] = wino.top().stl["break_update"] = wino.top().stl["weapon_update"] = 0;
    }    
    ita(wino.top().screen["screen"] , wino.top().screen["status"] , 0 , y-5 , 0);
}