
// window for first boot
// dammm how cool is it , its like making a os, &_&

#include "boot.h"
#include "../output/output.h"
#include "../stora/stora.h"
#include "window.h"
#include "../lib.h"

void boot(){
    first_boot=0;
    string s = "booting..";
    s = paint(s , "green");
    s.push_back('\n');
    print_screen(s);
    if(isf()){
        s+= paint("data found , loading" , "green");
        print_screen(s);
        // work in process
    }
    else {
        s+= paint("data not found , initializing" , "red");
        print_screen(s);
        popwin();
        win apolo;
        apolo.name = "scro";
        pushwin(apolo);
    }
}
