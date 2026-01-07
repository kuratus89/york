#include "lib.h"
#include "output/output.h"
#include "input/input.h"
#include "stora/stora.h"
#include "windows/window.h"

using namespace std;



int main(){
    input::event e;
    cout << "\033[?25l";
    while(gameon){//main game loop >_<
        if(input::pollEvent(e))k=input::keyToString(e.keycode);
        else k="-";
        window();
        
    }
}