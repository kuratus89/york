#include "../window.h"
#include "../../output/output.h"
#include "../../game/chunk.h"
#include "../../game/core.h"
#include <random>

int randi(){
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dist(10000, 99999);
    return dist(gen);
}

void inta(){
    if(k=="W")wino.top().stl["selecter"]--;
    if(k=="S")wino.top().stl["selecter"]++;
    if(wino.top().stl["selecter"]==4)wino.top().stl["selecter"]=0;
    if(wino.top().stl["selecter"]<0)wino.top().stl["selecter"]=3;
    if(k=="Enter"){
        if(wino.top().stl["selecter"]==0){
            win in;
            in.name = "input_str";
            in.sts["api"]="world_name";
            in.stl["limit"] = 10;
            wino.push(in);
        }
        else if(wino.top().stl["selecter"]==1){
            win in;
            in.name = "input_str";
            in.stl["only_int"]=1;
            in.sts["api"] = "seed";
            in.stl["limit"] = 10;
            wino.push(in);
        }
        else if(wino.top().stl["selecter"]==2){
            if(wino.top().sts["world_name"]==""){
                win msg;
                msg.name = "msg";
                msg.stl["color"] = 0;
                msg.sts["title"] = "name?";
                msg.vs["msg"] = {"You want to create world without a name? wow!","","Enter the fucking name u idiot !!","","umm , i am really sorry for this behavior , but really? u want to create world without name?"};
                wino.push(msg);
            }
            else {
                if(wino.top().sts["seed"]=="")ear.seed = randi();
                else ear.seed = stoi(wino.top().sts["seed"]);
                ear.name = wino.top().sts["world_name"];
                ear.posy = cy=height(cx)-1;
                ear.posx= 0;
                win mg;
                filesystem::create_directories("data/worlds/"+ear.name);
                if(!ear.save("data/worlds/"+ear.name+"/data.kp")){
                    mg.name = "error";
                    mg.sts["value"] = "cant save world files , cant create world!";
                }
                else mg.name = "main_game";
                
                wino.pop();
                wino.push(mg);
            }
        }
        else wino.pop();
    }
}

void start_new_game(){
    vector<string> opts{
        "World Name :",
        "seed(leave blank for random seed) :",
        "Start!",
        "Back"
    };
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        wino.top().screen["screen"] = pre_screen;
        wino.top().screen_handle=1;
        wino.top().screen["pika"];
        wino.top().stl["selecter"]=0;
    }
    if(wino.top().sts["world_name"]!="")opts[0]+=wino.top().sts["world_name"];
    if(wino.top().sts["seed"]!="")opts[1]+= wino.top().sts["seed"];
    option_adder(wino.top().screen["pika"] , opts , wino.top().stl["selecter"] , 50  , 8);
    ita(wino.top().screen["screen"] , wino.top().screen["pika"] ,( (wino.top().screen["screen"][0].size() - wino.top().screen["pika"][0].size()-2)/2)+1 , ((wino.top().screen["screen"].size() - wino.top().screen["pika"].size()-2)/2)+1);
    inta();
}