#ifndef OUTPUT_H
#define OUTPUT_H
#include "../lib.h"
#include "clear_screen.h"
string dommer(vector<vector<pair<char , char>>> &screen);
void print_screen(string screen);
string paint(string s , string col);
vector<vector<pair<char , char>>> bod_create(char colo , long long lx , long long ly);
void kuramizer(vector<vector<pair<char , char>>> &screen);
void dialog_seprater(char colo , vector<vector<pair<char , char>>> &scro);void par_scr(vector<vector<pair<char, char>>> &screen,vector<vector<pair<char, char>>> &par , long long vx , long long vy);
void dialog_adder(vector<vector<pair<char , char>>> &scro , string name , char player_icon , string msg , char colo);
void ovr(string vallo);
#endif