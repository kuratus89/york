
// manage windows (.)-(.)

#include "window.h"
#include <bits/stdc++.h>
#include "boot.h"
#include "scro.h"
#include "../stora/stora.h"
#include "error.h"
using namespace std;



map<string , void(*)()> func_point = {
        {"boot" , boot},
        {"error", error},
        {"scro" , scro}
};


void window(){
    if(wino.empty()){
        win tamzid;
        tamzid.type=1;
        if(first_boot)tamzid.name="boot";
        else {
            tamzid.name="error";
            tamzid.sts["value"]="stack window empty";
        }
        wino.push(tamzid);
    }
    func_point[wino.top().name];
}

void popwin(){
    wino.pop();
}
void pushwin(win ararara){
    wino.push(ararara);
}