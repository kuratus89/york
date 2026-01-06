#include "output.h"
#include "clear_screen.h"
#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<char , char>>> cur_screen;
map<string , string> string_to_color={
    {"red","\033[31m"},
    {"blue" ,"\033[34m"},
    {"green" , "\033[32m"},
    {"purple" , "\033[35m"},
    {"cyan" , "\033[36m"},
    {"white" , "\033[37m"},
    {"reset" , "\033[0m"}
};
vector<string> in_to_color = {"\033[31m" ,"\033[34m","\033[32m","\033[35m","\033[36m","\033[37m","\033[0m"};

string dommer(vector<vector<pair<char , char>>> &screen){// dommer process the screen data to string :)
    string s;
    for(auto vol:screen){
        for(auto val:vol){
            string colo = in_to_color[val.first -'0'];
            for(auto hulululu:colo)s.push_back(hulululu);
            s.push_back(val.second);
        }
        s.push_back('\n');
    }
    return s;
}

void print_screen(string screen){
    soft_clear();
    cout<<screen;
}
