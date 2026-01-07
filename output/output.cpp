#include "../lib.h"
#include "output.h"
#include "clear_screen.h"
#include "../stora/stora.h"



string paint(string s ,string col ){//paint string with color
    s = string_to_color[col] + s + string_to_color["white"];
    return s;
}

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
    cout<<string_to_color["white"];
    return s;
}

void print_screen(string screen){// output the string with soft clear
    soft_clear();
    cout<<screen;
}



