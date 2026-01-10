
#include "../lib.h"
#include "../stora/stora.h"
#include "../physics/physics.h"
#include "../output/output.h"
long long tarx;
bool ani=1;
long long di=0;
long long din=0;
string dial;
void initilize_tarx(){
    tarx = ((x-2)/2)+1;
}

void dialoger(){
    if(din>intro_dialog[di].size()){
        if(k==" "){
            di++;
            dial="";
            din=0;
        }        
    }
    else {
        dial.push_back(intro_dialog[di][din]);
        din++;
        dialog_adder(wino.top().screen , "unknown" , player , dial , '5');
    }
    

}

void intro(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen = bod_create('5' , x , y);
        dialog_seprater('5', wino.top().screen );
        initilize_tarx();
        player_color = '5';
        cx = 3;
        cy= 1;
        player = '@';
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["done"]=0;
    }
    if(ani){
        wino.top().screen[cy][cx].second=' ';
        if(isbo()){
            if(cx==tarx){
                ani=0;
            }
            else cx++;
        }
        else {
            cy++;
        }
        wino.top().screen[cy][cx]= {'5' , player};
    }
    else {
        if(di<intro_dialog.size()){
            dialoger();
        }
        else {
            if(wino.top().stl["done"]==0){
                // wino.pop();
                win hehe;
                hehe.name = "intro_menu";
                wino.push(hehe);
            }
            else {
                wino.pop();
                win heha;
                heha.name = "main_menu";
                wino.push(heha);
            }
        }
    }
    delay(30);

    
}