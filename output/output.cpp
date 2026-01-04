#include "output.h"
#include "clear_screen.h"
#include <bits/stdc++.h>
using namespace std;
string cur_screen ="";
void screen_output(string screen){
    if(cur_screen==screen)return;
    if(cur_screen.size()<=screen.size())soft_clear();
    else hard_clear();
    cout<<screen;
    cur_screen=screen;
}