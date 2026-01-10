
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
    if(boot_log)this_thread::sleep_for(std::chrono::milliseconds(200));
    print_screen(s);
    if(boot_log)this_thread::sleep_for(std::chrono::milliseconds(200));
    if(isf()){
        s+= paint("data found , loading" , "green");
        print_screen(s);
        win beluga;
        beluga.name = "main_menu";
        wino.push(beluga);
    }
    else {
        s+= paint("data not found , initializing" , "red");
        print_screen(s);
        popwin();
        win kalu;
        kalu.name="intro";
        wino.push(kalu);
        win apolo;
        apolo.name = "scro";
        pushwin(apolo);
        hc=1;
        if(boot_log)this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
}
