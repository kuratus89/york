
#include "../windows/window.h"
#include "chunk.h"
#include "../output/output.h"
#include "../input/input.h"
#include "../physics/physics.h"
#include "core.h"
#include "../windows/dynamic/inventory.h"

pixel pa , pp;

void game_window(){
    wino.top().screen["game"] = vector<vector<pixel>> (y , vector<pixel> (x , pa));
    render(wino.top().screen["game"] , cx , cy);
}
void init(){
    // if(k=="W")cy--;
    // if(k=="S")cy++;
    // if(k=="A")cx--;
    // if(k=="D")cx++;
    if(input::ikd(input::key::Space))jump();
    if(input::ikd(input::key::A))move_left();
    if(input::ikd(input::key::D))move_right();
    if(input::ikd(input::key::Shift)){
        if(input::ikd(input::key::Up))break_block_up();
        if(input::ikd(input::key::Down))break_block_down();
        if(input::ikd(input::key::Left))break_block_left();
        if(input::ikd(input::key::Right))break_block_right();
    }
    else {
        
        if(input::ikd(input::key::Up)){
            if(ear.inventory[item]<=0)return;
            place_block_up(item);
            ear.inventory[item]--;
        }
        if(input::ikd(input::key::Down)){
            if(ear.inventory[item]<=0)return;
            place_block_down(item);
            ear.inventory[item]--;
        }
        if(input::ikd(input::key::Left)){
            if(ear.inventory[item]<=0)return;
            place_block_left(item);
            ear.inventory[item]--;            
        }
        if(input::ikd(input::key::Right)){
            if(ear.inventory[item]<=0)return;
            place_block_right(item);
            ear.inventory[item]--;
        }
    }
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
}

void main_game(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
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
        
    }
    manage_jump();
    gravity();
    manage_chunks(cx , cy);
    game_window();
    ita(wino.top().screen["screen"] , wino.top().screen["game"] , 0 , 0);
    ita(wino.top().screen["screen"] , wino.top().screen["player"] , (x/2), (y/2));
    init();
    delay(20);
}