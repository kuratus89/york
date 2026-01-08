
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"

void intro_menu(){
    auto &gura = wino.top();
    if(!gura.initilizzed){
        gura.initilizzed=1;
        gura.type=1;
        gura.screen = pre_screen;
        gura.par_screen = bod_create('5' , 20 , 10);
        gura.screen_handle=1;
        string title = "ENTER DETAILS";
        long long lox= (max(0LL,(long long)gura.par_screen[0].size()-(long long)title.size()-2)/2)+1;
        for(auto &val:title){
            if(lox>=gura.par_screen[0].size()-1)break;
            gura.par_screen[0][lox]={'5',val};
            lox++;
        }
    }
    
    par_scr(gura.screen , gura.par_screen , 3 , 3);


}