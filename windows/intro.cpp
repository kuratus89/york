
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
        dialog_adder(wino.top().screen["screen"] , "unknown" , player , dial , 5);
    }
    

}
void dia(){
    wino.top().screen["dia"] = bod_create(5 , x , 5);
    wino.top().screen["dia"][0][0].value = "├";
    wino.top().screen["dia"][0][x-1].value = "┤"; 
}

void intro(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen["screen"] = bod_create(5 , x , y);
        // dialog_seprater('5', wino.top().screen["screen"] );
        initilize_tarx();
        player_color = 5;
        player = '@';
        wino.top().screen_handle =1;
        wino.top().type=1;
        wino.top().stl["done"]=0;
        dia();
        ita(wino.top().screen["screen"] , wino.top().screen["dia"] , 0 , y-5 , 1);

    }
    
    if(ani){
        wino.top().screen["screen"][cy][cx].value=" ";
        if(isbo()){
            if(cx==tarx){
                ani=0;
            }
            else cx++;
        }
        else {
            cy++;
        }
        pixel pe;
        pe.color = 5;
        pe.value = string(1,player);
        wino.top().screen["screen"][cy][cx]= pe;
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
                return;
            }
            else {
                wino.pop();
                win heha;
                heha.name = "main_menu";
                wino.push(heha);
                return;
            }
        }
    }
    delay(30);
    
    
}