
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"
#include "../physics/physics.h"

void main_menu(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().blank_screen = bod_create('5' , x , y);
        dialog_seprater('5' , wino.top().blank_screen);
        wino.top().screen = wino.top().blank_screen;
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["stage"]=1;
        wino.top().stl["xtar"]= x-22;
        // wino.top().stl["ytar"]=y-2;
        wino.top().stl["posd"]=0;       
    }
    // wino.top().screen[cy][cx] = {'5' , ' '};
    if(wino.top().stl["posd"]==0){
        wino.top().screen = wino.top().blank_screen;
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
    else if(wino.top().stl["posd"]==1){
        wino.top().screen = wino.top().blank_screen;
        delay(80);
        wino.top().screen[cy][cx-6]= {'5' , '<'};
        wino.top().screen[cy][cx+6] = {'5' , '>'};
        for(long long i=cx-5 ; i<=cx+5 ; i++)wino.top().screen[cy][i] = {'5' , '='};
        for(long long i=y-6 ; i>cy ; i--)wino.top().screen[i][cx]= {'5' , '#'};
        cy--;
        if(cy==((y-2)/2))wino.top().stl["posd"]=2;
    }
    else {
        
    }
    wino.top().screen[cy][cx] = {player_color , player};

}