
// manage windows (.)-(.)

#include "boot.h"
#include "error.h"
#include "scro.h"
#include "../stora/stora.h"
#include "intro.h"
#include "../output/output.h"
#include "../lib.h"



map<string , void(*)()> func_point = {
        {"boot" , boot},
        {"error", error},
        {"scro" , scro},
        {"intro" , intro}
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
    func_point[wino.top().name]();
}

void popwin(){
    wino.pop();
}
void pushwin(win ararara){
    wino.push(ararara);
}