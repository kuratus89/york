#include "lib.h"
#include "output/output.h"
#include "input/input.h"
#include "stora/stora.h"
#include "windows/window.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


void init_console() {
    SetConsoleOutputCP(CP_UTF8);
}

void cap(int target_fps , double ls){
    if(speed)return;
    double target_ms = 1000.0/(target_fps*2);
    double remain = max(0.0, target_ms - ls);
    this_thread::sleep_for(std::chrono::microseconds((int)(remain*1000)));
}


int main(){
    input::event e;
    init_console();
    cout << "\033[?25l";
    
    while(gameon){//main game loop >_<
        auto start = chrono::high_resolution_clock::now();
        if(input::pollEvent(e))k=input::keyToString(e.keycode);
        else k="-";
        window();
        cap(target_fps , (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()- start)).count()/1000.0);
        ms = (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()-start)).count()/1000.0;        
    }
}