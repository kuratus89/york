#include <bits/stdc++.h>
#include "output/output.h"

#include "input/input.h"
using namespace std;

//variable=>
bool gameon=1;
string k="-";
string s="hi";

int main(){
    input::event e;
    cout << "\033[?25l";
    while(gameon){//main game loop
        screen_output(s);
        if(input::pollEvent(e)){
            k=input::keyToString(e.keycode);
        }
        else k="-";
        if(k!="-")s+=k;
    }
}