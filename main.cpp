#include <bits/stdc++.h>
#include "output/output.h"

#include "input/input.h"
using namespace std;

//variable=>
bool gameon=1;
string k="-";
string s="hi";
long long t=0;
vector<string> col = {"red" , "green" , "blue" , "cyan" , "purple"};
long long x=5;
long long y=5;
vector<vector<pair<char , char>>> screen;


vector<vector<pair<char , char>>> scgen(){
    vector<vector<pair<char , char>>> sc(y , vector<pair<char, char>> (x));
    for(long long i=0 ; i<y ; i++){
        for(long long j=0; j<x ; j++){
            sc[i][j]={('0'+((i+j)%5)),'#'};
        }
    }
    return sc;
}

int main(){
    input::event e;
    cout << "\033[?25l";
    while(gameon){//main game loop
        screen = scgen();
        print_screen(dommer(screen));
        if(input::pollEvent(e))k=input::keyToString(e.keycode);
        else k="-";
        if(k=="D")x++;
        else if(k=="S")y++;
    }
}