
#include "../windows/window.h"
#include "chunk.h"
#include "../output/output.h"
#include "../input/input.h"
#include "../physics/physics.h"
#include "core.h"

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
}

void main_game(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
        wino.top().adv=1;
        pa.color=5;
        pa.value = " ";
        cx=0;
        cy=height(cx)-1;
        wino.top().screen["screen"] = vector<vector<pixel>> (y , vector<pixel> (x ,pa));
    
        pp.color = player_color;
        pp.value = string(1,player);
        wino.top().screen["player"] = vector<vector<pixel>> (1 , vector<pixel> (1 , pp));
        
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