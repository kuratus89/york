#ifndef OUTPUT_H
#define OUTPUT_H
#include "../lib.h"
#include "clear_screen.h"
#include "../stora/stora.h"
string dommer(vector<vector<pair<char , char>>> &scr);
void print_screen(string screen);
string paint(string s , string col);
void text_adder(vector<vector<pixel>> &screen , int x , int y , string s , int color);
vector<vector<pixel>> bod_create(int colo , long long lx , long long ly  );
// void kuramizer(vector<vector<pair<char , char>>> &screen);
void dialog_seprater(char colo , vector<vector<pair<char , char>>> &scro);void par_scr(vector<vector<pair<char, char>>> &screen,vector<vector<pair<char, char>>> &par , long long vx , long long vy);
void dialog_adder(vector<vector<pixel>> &scro , string name , char player_icon , string msg , int colo);
void ovr(string vallo);
void option_adder(vector<vector<pixel>> &screen , vector<string> &options , long long selecter , int x , int y , bool boder);
void kuramizer(vector<vector<pixel>> &screen);
void ita(vector<vector<pixel>> &screen,vector<vector<pixel>> &par,int vx, int vy , bool boder);
void fad(vector<vector<pixel>> &screen , bool &fps , bool &latency , double &ms);
void vertical_window_align(vector<vector<pixel>> &result , vector<vector<pixel>> &top , vector<vector<pixel>> &bottom , bool center_align , int space);
void horizontal_window_align(vector<vector<pixel>> &result , vector<vector<pixel>> &left , vector<vector<pixel>> &right , bool center_align , int space);
void text_to_win_xlim(vector<vector<pixel>> &win , string s , int x);
void bod_add(vector<vector<pixel>> &result , vector<vector<pixel>> &scr);
#endif