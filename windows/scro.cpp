
// initialize screen size [&]-[&]

#include "scro.h"
#include "../stora/stora.h"
#include "../output/output.h"
#include "window.h"
#include "../lib.h"
#include "../input/screen_size.h"
#include "dynamic/msg.h"

void scro(){
    if(!wino.top().initilizzed){
        wino.top().initilizzed=1;
        win message;
        message.name = "msg";
        message.sts["title"] = "INSTRUCTIONS";
        message.vs["msg"] = {
            "PLEASE MAXIMIZE YOUR WINDOW",
            "PRESS ENTER TO CONTINUE"
        };
        message.sts["color"] = "1";
        wino.push(message);
        pair<int, int> size = screen_size();
        x = size.first;
        pixel pe;
        pe.color = 5;
        pe.value = " ";
        y = size.second;
        wino.top().screen["screen"] = vector<vector<pixel>> (y , vector<pixel> (x , pe));
        pre_screen =vector<vector<pixel>> (y , vector<pixel> (x , pe));
        return;
        
    }
    pair<int, int> size = screen_size();
    x = size.first;
    y = size.second;
    wino.pop();
}