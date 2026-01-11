
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
        y = size.second;
        wino.top().screen["screen"] = vector<vector<pair<char , char>>> (y , vector<pair<char , char>> (x , {'5' , ' '}));
        pre_screen = vector<vector<pair<char , char>>> (y , vector<pair<char , char>> (x , {'5' , ' '}));
        return;
        
    }
    pair<int, int> size = screen_size();
    x = size.first;
    y = size.second;
    wino.pop();
}