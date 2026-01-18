#include "../../lib.h"
#include "../window.h"
#include "../../output/output.h"
#include "../../game/chunk.h"

vector<string> invoda = {
    "Air",
    "Grass",
    "Stone",
    "iron",
    "gold",
    "diamond"
};


int item=0;
vector<string> invd;
vector<int> tempo;
void itp(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]==invd.size())wino.top().stl["selecter"]=0;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"] = invd.size()-1;
    if(k=="Enter"){
        item = tempo[wino.top().stl["selecter"]];
        wino.pop();
    }
}

void inventory(){
    
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen_handle =1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().stl["selecter"]=0;
        invd.clear();
        tempo.clear();
        for(auto &val:ear.inventory){
            if(val.second==0)continue;
            invd.push_back(invoda[val.first] + " : " + to_string(val.second));
            tempo.push_back(val.first);
        }
        if(invd.empty()){
            wino.pop();
            win msg;
            msg.name = "msg";
            msg.vs["msg"] = {"INVENTORY IS EMPTY!","" , "GO AND BREAK SOME BLOCKS!"};
            msg.stl["color"]=0;
            wino.push(msg);
            return;
        }
    }
    option_adder(wino.top().screen["invo"] , invd , wino.top().stl["selecter"] , 20 , 10);
    ita(wino.top().screen["screen"] , wino.top().screen["invo"] , LLONG_MIN , LLONG_MIN , 1);
    itp();
}
