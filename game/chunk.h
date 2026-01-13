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
struct chunks{
    long long x;
    long long y;
    bool always_load=0;
    vector<vector<int>> chunk = vector<vector<int>> (10 , vector<int> (10));
};
void render(vector<vector<pixel>> &scv , long long mx , long long my );
void chunk_unloader(long long lvx , long long lvy);
void chunk_loader(long long lcx , long long lcy);
void manage_chunks(long long px , long long py);


#endif