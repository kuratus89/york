#include <bits/stdc++.h>
#include "output/output.h"
#include "input/input.h"
#include "stora.h"
#include "windows/window.h"

using namespace std;

//global variable=>


int main(){
    input::event e;
    cout << "\033[?25l";
    while(gameon){//main game loop >_<
        if(input::pollEvent(e))k=input::keyToString(e.keycode);
        else k="-";
        window();
        
    }
}