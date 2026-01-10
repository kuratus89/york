
// manage windows (.)-(.)

#include "boot.h"
#include "error.h"
#include "scro.h"
#include "../stora/stora.h"
#include "intro.h"
#include "../output/output.h"
#include "dynamic/intro_menu.h"
#include "dynamic/input_str.h"
#include "dynamic/msg.h"
#include "main_menu.h"
#include "../lib.h"



map<string , void(*)()> func_point = {
        {"boot" , boot},
        {"error", error},
        {"scro" , scro},
        {"intro" , intro},
        {"intro_menu" , intro_menu},
        {"input_str" , input_str},
        {"msg" , msg},
        {"main_menu" , main_menu}
};


void window(){
    if(hc){
        hard_clear();
        hc=0;
    }
    if(wino.empty()){
        win tamzid;
        tamzid.type=1;
        if(first_boot)tamzid.name="boot";
        else {
            hc=1;
            tamzid.name="error";
            tamzid.sts["value"]="stack window empty";
        }
        wino.push(tamzid);
        return;
    }
    try{
        func_point[wino.top().name]();
    }
    catch(exception &e){
        string s = "window -> ";
        s+=wino.top().name;
        s+= " crash , error -> ";
        s+= e.what();
        win valaray;
        valaray.name = "error";
        valaray.sts["value"]=s;
        wino.push(valaray);
        return;
    }
    

    if(wino.top().screen_handle){
        // if(wino.top().type){
        //     kuramizer(wino.top().screen);
        // }
        // else {
        //     par_scr(wino.top().screen , wino.top().clx , wino.top().cly);
        // }
        kuramizer(wino.top().screen["screen"]);
        
    }
}

void popwin(){
    wino.pop();
}
void pushwin(win ararara){
    wino.push(ararara);
}