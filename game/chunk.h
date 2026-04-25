#ifndef CHUNK_H
#define CHUNK_H
#include "../lib.h"
#include "../stora/stora.h"
// struct block{
//     int value;
//     int color;
//     // there are many more things in my mind to add
//     // i will add later
// };


void render(vector<vector<pixel>> &scv , long long mx , long long my );
void chunk_unloader(long long lvx , long long lvy);
void chunk_loader(long long lcx , long long lcy);
void manage_chunks(long long px , long long py);
int get_block(long long x, long long y);
void set_block(long long x, long long y , int d);
bool save_game(string s);
void manage_all_mobs();
void spawn_mob(int lx , int ly , int type);
int get_mob(long long x , long long y);
mob& get_mob_id(long long x , long long y);
chunks* chunk_pointer(int lx , int ly);
extern world ear;
extern long long chunk_size;
extern vector<pair<string , pair<string, int>>> blocker;

#endif