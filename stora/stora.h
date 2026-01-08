#ifndef STORA_H
#define STORA_H

#include "../lib.h"

 //variables 

extern bool isf();
struct win{
    bool type;// type 1 => full window , type 0 => partial window
    string name;// window name
    // data
    map<string , string> sts;
    map<string , long long> stl;
    // map<long long , string> lts;
    // map<long long , long long> ltl;
    vector<vector<pair<char , char>>> screen;
    vector<vector<pair<char , char>>> par_screen;
    bool initilizzed=0;
    bool screen_handle=0;
};
extern bool gameon;
extern stack<win> wino;
extern bool first_boot;
extern string k;
extern map<string , string> string_to_color;
extern vector<string> in_to_color;
extern long long x,y;
extern long long xmin;
extern long long ymin;
extern long long ymax;
extern long long xmax;
extern bool hc;
extern bool ch;
extern long long rx;
extern long long ry;
extern bool boot_log;
extern long long cx;
extern long long cy;
extern char player;
// extern vector<vector<pair<char , char>>> screen;
extern vector<vector<pair<char , char>>> pre_screen;
extern string player_color;
extern vector<string> intro_dialog;

//func



#endif