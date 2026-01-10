#ifndef STORA_H
#define STORA_H

#include "../lib.h"

 //variables 

bool isf();
struct win{
    bool type;// type 1 => full window , type 0 => partial window
    string name;// window name
    // data
    map<string , string> sts;
    map<string , long long> stl;
    // map<long long , string> lts;
    // map<long long , long long> ltl;
    map<string , vector<vector<pair<char , char>>>> screen;
    map<string ,vector<string>> vs;
    bool initilizzed=0;
    bool screen_handle=0;
    
};
struct boot_data{
    map<string , string> sts;
    map<string , long long> stl;
};
bool save_boot_data(const boot_data &data, const std::string &valo, const std::string &dgm);
bool load_boot_data(const string &valo, const string &dgm, boot_data &out_data);
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
extern char player_color;
extern vector<string> intro_dialog;
extern vector<vector<pair<char , char>>> title;

//func



#endif