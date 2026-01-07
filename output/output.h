#ifndef OUTPUT_H
#define OUTPUT_H
#include "../lib.h"
#include "clear_screen.h"
string dommer(vector<vector<pair<char , char>>> &screen);
void print_screen(string screen);
string paint(string s , string col);
vector<vector<pair<char , char>>> bod_create(char colo);
void kuramizer();
void dialog_adder(vector<vector<pair<char , char>>> &scro , string name , char player_icon , string msg , char colo);
#endif