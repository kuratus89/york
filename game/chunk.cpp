
#include "../lib.h"
#include "chunk.h"
#include "core.h"
#include "../stora/stora.h"

long long grass_lvl=10;
vector<chunks> chunker;
long long render_distance = 300;
vector<string> blocker{
    " ",
    "#"
};

void chunk_loader(long long lcx , long long lcy){
    chunks jk;
    jk.x = lcx;
    jk.y = lcy;
    for(long long i=0 ; i<10; i++){
        long long h = height(lcx+i);
        for(long long j=0 ; j<10 ; j++){
            block bk;
            if(lcy+j<h){
                bk.value = 0;
                bk.color =0;
            }
            else {
                bk.value =1;
                if(lcy+j<grass_lvl)bk.color = 2;
                else bk.color =1;
            }
            jk.chunk[i][j] = bk;
        }
    }
    chunker.push_back(jk);

}
void chunk_unloader(long long lvx , long long lvy){
    for(long long i=0 ; i<chunker.size() ;i++){
        if(((abs(lvx - chunker[i].x)>render_distance)||((abs(lvy - chunker[i].y)>render_distance)))&&(!chunker[i].always_load)){
            swap(chunker[i] , chunker.back());
            chunker.pop_back();
            i--;
        }
    }
}
void chaper(vector<vector<pixel>> &scv , vector<vector<block>> &chk , long long vx , long long vy){
    for(long long i = 0; i < chk.size(); ++i){
        long long tx = vx + i;
        if(tx < 0 || tx >= scv[0].size()) continue;

        for(long long j = 0; j < chk[i].size(); ++j){
            long long ty = vy + j;
            if(ty < 0 || ty >= scv.size()) continue;

            pixel pix;
            pix.color = chk[i][j].color;
            pix.value = blocker[chk[i][j].value];
            scv[ty][tx] = pix;
        }
    }
}

void render(vector<vector<pixel>> &scv , long long mx , long long my ){
    for(auto &val:chunker){
        chaper(scv , val.chunk , val.x - mx, val.y - my);
    }
}

bool is_chunk_loaded(long long x, long long y) {
    for(const auto &c : chunker) {
        if(c.x == x && c.y == y) return true;
    }
    return false;
}

void manage_chunks(long long px, long long py) {
    chunk_unloader(px, py);
    long long gx = floor(px / 10.0)*10;
    long long gy = floor(py / 10.0)*10;
    for (long long x = gx - render_distance; x <= gx + render_distance; x += 10) {
        for (long long y = gy - render_distance; y <= gy + render_distance; y += 10) {
            if (!is_chunk_loaded(x, y)) {
                chunk_loader(x, y);
            }
        }
    }
}