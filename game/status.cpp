#include "../output/output.h"
#include "../windows/window.h"
#include "../stora/stora.h"
#include "chunk.h"
#include "../windows/dynamic/inventory.h"
#include "weapon.h"
#include "../physics/physics.h"

void healther(){
    for(long long i=1 ; i<=10; i++)wino.top().screen["health"][1][i].value = " ";
    int col;
    if(ear.health>50)col = 2;
    else if(ear.health>30)col = 1;
    else col = 0;
    pixel he;
    he.color = col;
    he.value = "█";
    for(long long i=1 ; i<=((ear.health*10)/max_health) ; i++)wino.top().screen["health"][1][i]=he;
    ita(wino.top().screen["status"] ,wino.top().screen["health"] , 17 , 1 ,1);

}
void breaker(){
    for(long long i=1 ; i<=10; i++)wino.top().screen["breaker"][1][i].value = " ";
    int col;
    pixel be;
    be.color = 5;
    be.value = "█";
    if(max_break_block!=0)for(long long i=1 ; (i< ((break_block*10)/max_break_block)&&(i<=10)); i++)wino.top().screen["breaker"][1][i] = be;
    ita(wino.top().screen["status"] , wino.top().screen["breaker"] ,47 , 1 , 1 );
}

void selected(){
    pixel px;
    px.color = blocker[item].second.second;
    px.value = blocker[item].second.first;
    wino.top().screen["item"][1][1] = px;
    wino.top().screen["item"][1][2] = px;
    ita(wino.top().screen["status"] , wino.top().screen["item"] , 35 , 1 , 1);
}

void add_weapon_in_status(){
    int i = wino.top().stl["wp"]+7;
    for(auto val:selected_weapon){
        if(i==x)break;
        wino.top().screen["status"][2][i].value = val;
        i++;
    }
}

void status(){
    if(wino.top().stl["status_initilize"]!=1){
       wino.top().stl["status_initilize"]=1;
        wino.top().screen["health"] = bod_create( 5,12, 3);
        wino.top().screen["breaker"] = bod_create(5 , 12 , 3);
        wino.top().screen["status"] = bod_create(5 , x , 5);
        for(long long i=1 ; i<5-1; i++)wino.top().screen["status"][i][8].value = "|";
        wino.top().screen["status"][1][5].color = player_color;
        wino.top().screen["status"][1][5].value = string(1,player);
        wino.top().screen["status"][2][10].value = "H";
        wino.top().screen["status"][2][11].value = "e";
        wino.top().screen["status"][2][12].value = "a";
        wino.top().screen["status"][2][13].value = "l";
        wino.top().screen["status"][2][14].value = "t";
        wino.top().screen["status"][2][15].value = "h";
        wino.top().screen["status"][2][16].value = ":";


        wino.top().screen["status"][2][30].value = "I";
        wino.top().screen["status"][2][31].value = "t";
        wino.top().screen["status"][2][32].value = "e";
        wino.top().screen["status"][2][33].value = "m";
        wino.top().screen["status"][2][34].value = ":";

        long long wp=40;
        wino.top().stl["wp"]=60;

        wino.top().screen["status"][2][wino.top().stl["wp"]].value = "W";
        wino.top().screen["status"][2][wino.top().stl["wp"]+1].value = "e";
        wino.top().screen["status"][2][wino.top().stl["wp"]+2].value = "a";
        wino.top().screen["status"][2][wino.top().stl["wp"]+3].value = "p";
        wino.top().screen["status"][2][wino.top().stl["wp"]+4].value = "o";
        wino.top().screen["status"][2][wino.top().stl["wp"]+5].value = "n";
        wino.top().screen["status"][2][wino.top().stl["wp"]+6].value = ":";

        wino.top().stl["bp"] = 40;
        wino.top().screen["status"][2][wino.top().stl["bp"]].value = "B";
        wino.top().screen["status"][2][wino.top().stl["bp"]+1].value = "r";
        wino.top().screen["status"][2][wino.top().stl["bp"]+2].value = "e";
        wino.top().screen["status"][2][wino.top().stl["bp"]+3].value = "a";
        wino.top().screen["status"][2][wino.top().stl["bp"]+4].value = "k";
        wino.top().screen["status"][2][wino.top().stl["bp"]+5].value = ":";

        wino.top().screen["item"] = bod_create(5 , 4 , 3);
        long long temp = 1;
        for(auto val:player_name){
            wino.top().screen["status"][2][temp].value = val;
            temp++;
        }

        
    }
    healther();
    selected();
    add_weapon_in_status();
    breaker();
    ita(wino.top().screen["screen"] , wino.top().screen["status"] , 0 , y-5 , 0);
    
}