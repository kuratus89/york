#ifndef OUTPUT_H
#define OUTPUT_H
#include "../lib.h"
#include "clear_screen.h"
#include "../stora/stora.h"
string dommer(vector<vector<pair<char , char>>> &screen);
void print_screen(string screen);
string paint(string s , string col);
vector<vector<pixel>> bod_create(int colo , long long lx , long long ly  );
// void kuramizer(vector<vector<pair<char , char>>> &screen);
void dialog_seprater(char colo , vector<vector<pair<char , char>>> &scro);void par_scr(vector<vector<pair<char, char>>> &screen,vector<vector<pair<char, char>>> &par , long long vx , long long vy);
void dialog_adder(vector<vector<pixel>> &scro , string name , char player_icon , string msg , int colo);
void ovr(string vallo);
void option_adder(vector<vector<pixel>> &screen , vector<string> &options , long long selecter , long long sx , long long sy);
void kuramizer(vector<vector<pixel>> &screen);
void ita(vector<vector<pixel>> &screen,vector<vector<pixel>> &par,long long vx, long long vy , bool boder);

#endif