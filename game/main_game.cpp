
#include "../windows/window.h"
#include "chunk.h"
#include "../output/output.h"
#include "../input/input.h"
#include "../physics/physics.h"
#include "core.h"
#include "../windows/dynamic/inventory.h"
#include "weapon.h"
#include "status.h"
#include "npc.h"
#include "../skill/skill_main.h"

pixel pa , pp;

void game_window(){
    wino.top().screen["game"] = vector<vector<pixel>> (y , vector<pixel> (x , pa));
    render(wino.top().screen["game"] , cx , cy);
}
void init(){
    
    if(input::ikd(input::key::Space))jump();
    if(input::ikd(input::key::A))move_left(cx , cy);
    if(input::ikd(input::key::D))move_right(cx , cy);
    // if(!input::ikd(input::key::Shift))breaking =0;
    if(input::ikd(input::key::Shift)){
        
        // if(input::ikd(input::key::Up))break_block_up();
        // if(input::ikd(input::key::Down))break_block_down();
        // if(input::ikd(input::key::Left))break_block_left();
        // if(input::ikd(input::key::Right))break_block_right();

        if(input::ikd(input::key::Up))block_breaker(cx , cy-1 , ear.inventory);
        else if(input::ikd(input::key::Down))block_breaker(cx , cy+1 , ear.inventory);
        else if(input::ikd(input::key::Left))block_breaker(cx-1 , cy , ear.inventory);
        else if(input::ikd(input::key::Right))block_breaker(cx+1 , cy , ear.inventory);
        else if(breaking)breaking =0;
    }
    else if(breaking)breaking =0;
    else if(input::ikd(input::key::Control)){
        if(input::ikd(input::key::Left))hit_left(selected_weapon);
        if(input::ikd(input::key::Right))hit_right(selected_weapon);
        if(input::ikd(input::key::Down))hit_down(selected_weapon);
        if(input::ikd(input::key::Up))hit_up(selected_weapon);
    }
    else {
        
        if(input::ikd(input::key::Up)){
            if(ear.inventory[item]<=0)return;
            place_block_up(item);
        }
        if(input::ikd(input::key::Down)){
            if(ear.inventory[item]<=0)return;
            place_block_down(item);
        }
        if(input::ikd(input::key::Left)){
            if(ear.inventory[item]<=0)return;
            place_block_left(item);         
        }
        if(input::ikd(input::key::Right)){
            if(ear.inventory[item]<=0)return;
            place_block_right(item);
        }
    }
    if(ghost){
        if(input::ikd(input::key::W))cy--;
        if(input::ikd(input::key::S))cy++;
    }
    if(k=="-")return;
    if(k=="Enter"){
        win pau;
        pau.name = "pause";
        wino.push(pau);
    }
    else if(k=="E"){
        win in;
        in.name = "inventory";
        wino.push(in);
    }
    else if(k=="V"){
        win we;
        we.name = "weapon";
        wino.push(we);
    }
    else if(k=="K"){
        win sk;
        sk.name = "skill";
        wino.push(sk);
    }
}

void main_game(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
        // reset_physics();
        wino.top().adv=1;
        pa.color=5;
        pa.value = " ";
        cx=ear.posx;
        cy=ear.posy;
        wino.top().screen["screen"] = vector<vector<pixel>> (y , vector<pixel> (x ,pa));
    
        pp.color = player_color;
        pp.value = string(1,player);
        wino.top().screen["player"] = vector<vector<pixel>> (1 , vector<pixel> (1 , pp));
        wino.top().stl["item"]=1;
        apply_skills();

        if(ear.stl["first_timer"]==0){
            ear.stl["first_timer"]=1;
            win dia;
            dia.name = "dialog";
            dia.vs["dialog"] = {
                "This is the world I live in!",
                "I will show you exactly how to take control of me.",
                "You can control my movement using the A and D keys.",
                "You can open my thoughts with E and select what I must carry then confirm it with Enter",
                "You can make me place the selected block using the arrow keys",
                "You can make me break blocks using Shift + arrow keys",
                "And yes you possess a special ability to freeze time itself. Press ENTER to stop the world."
                
            };
            dia.stl["player_color"] = player_color;
            dia.sts["player"] = string(1,player);
            dia.sts["name"] = player_name;
            ticker.push_back({2,dia});
            
        }
        
    }
    gravity(cx , cy);
    manage_jump();
    manage_chunks(cx , cy);
    game_window();
    ita(wino.top().screen["screen"] , wino.top().screen["game"] , 0 , 0 , 1);
    ita(wino.top().screen["screen"] , wino.top().screen["player"] , (x/2), (y/2) , 1);
    if(show_fps||show_latency){
        fad(wino.top().screen["fad"] , show_fps , show_latency , ms);
        ita(wino.top().screen["screen"] , wino.top().screen["fad"] , 1 ,1 , 0);
    }
    status();
    delay(10);
    
    manage_all_mobs();
    
    physics();
    manage_hit();
    
    init();
}