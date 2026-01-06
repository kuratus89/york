#ifndef STORA_H
#define STORA_H

bool isf();
struct win{
    bool type;// type 1 => full window , type 0 => partial window
    string name;// window name
    // data
    map<string , string> sts;
    map<long long , string> lts;
    map<string , long long> stl;
    map<long long , long long> ltl;
};
bool gameon;
stack<win> wino;
bool first_boot;
string k;
map<string , string> string_to_color;
vector<string> in_to_color;
long long x,y;
long long xmin;
long long ymin;
long long ymax;
long long xmax;
bool hc;
bool ch=0;
long long rx;
long long ry;
string scrostring;
#endif