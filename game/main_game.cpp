
#include "../windows/window.h"
#include "chunk.h"
#include "../output/output.h"

pixel px;

void game_window(){
    wino.top().screen["game"] = vector<vector<pixel>> (y , vector<pixel> (x , px));
    render(wino.top().screen["game"] , cx , cy);
}
void init(){
    if(k=="W")cy--;
    if(k=="S")cy++;
    if(k=="A")cx--;
    if(k=="D")cx++;
}

void main_game(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle=1;
        wino.top().adv=1;
        px.color=5;
        px.value=" ";
        wino.top().screen["screen"] = vector<vector<pixel>> (y , vector<pixel> (x ,px));
        cx=0;
        cy=0;
        
    }
    manage_chunks(cx , cy);
    game_window();
    ita(wino.top().screen["screen"] , wino.top().screen["game"] , 0 , 0);
    init();
}