#include "lib.h"
#include "output/output.h"
#include "input/input.h"
#include "stora/stora.h"
#include "windows/window.h"
#ifdef _WIN32
    #ifndef NOMINMAX
    #define NOMINMAX
    #endif
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

void init_console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}


int main(){
    input::event e;
    init_console();
    cout << "\033[?25l";
    
    while(gameon){//main game loop >_<
        if(input::pollEvent(e))k=input::keyToString(e.keycode);
        else k="-";
        window();
        
    }
}