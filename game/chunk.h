#ifndef CHUNK_H
#define CHUNK_H
#include "../lib.h"
#include "../stora/stora.h"


void render(vector<vector<pixel>> &scv , long long mx , long long my );
void chunk_unloader(long long lvx , long long lvy);
void chunk_loader(long long lcx , long long lcy);
void manage_chunks(int x , int y);
int get_block(int x , int y);
void set_block(int x , int y , int block);
bool save_game(string s);
void manage_all_mobs(vector<vector<pixel>> &scr);
void spawn_mob(int lx , int ly , int type);
int get_mob(int x , int y);
mob& get_mob_id(int x , int y);
chunks* chunk_pointer(int x , int y);
extern world ear;
extern long long chunk_size;
extern vector<pair<string , pair<string, int>>> blocker;

#endif