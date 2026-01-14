
#include "../lib.h"
#include "chunk.h"
#include "core.h"
#include "../stora/stora.h"

long long grass_lvl=10;
// vector<chunks> chunker;
map<pair<int , int> , chunks> chunker;
long long render_distance = 120;
vector<pair<string , pair<string, int>>> blocker{
    {"air",{" " , 5}},//0
    {"grass",{"█",2}},//1
    {"stone" , {"█" , 6}}//2
};
long long chunk_size = 10;

void chunk_loader(long long lcx , long long lcy){
    chunks jk;
    jk.x = lcx;
    jk.y = lcy;
    for(long long i=0 ; i<10; i++){
        long long h = height(lcx+i);
        long long g = grass(lcx +i);
        for(long long j=0 ; j<10 ; j++){
            if((lcy+j<h)||(is_air(lcx+i , lcy+j))){
                jk.chunk[j][i]=0;
                continue;
            }
            if((lcy+j<19)||(lcy+j<g)){
                jk.chunk[j][i] = 1;
                continue;
            }
            jk.chunk[j][i] = 2;
        }
    }
    chunker[{lcx,lcy}] = (jk);

}
void chunk_unloader(long long lvx , long long lvy){
    for(auto it = chunker.begin() ; it!=chunker.end() ;){
        if((abs((*it).second.x - lvx)>render_distance)||((abs((*it).second.y - lvy)>render_distance))){
            it = chunker.erase(it);
        }
        else it++;
    }
}
void chaper(vector<vector<pixel>> &scv , vector<vector<int>> &chk , long long vx , long long vy){
    for(long long i = 0; i < chk.size(); ++i){
        long long tx = vx + i;
        if(tx < 0 || tx >= scv[0].size()) continue;

        for(long long j = 0; j < chk[i].size(); ++j){
            long long ty = vy + j;
            if(ty < 0 || ty >= scv.size()) continue;

            pixel pix;
            pix.color = blocker[chk[j][i]].second.second;
            pix.value = blocker[chk[j][i]].second.first;
            scv[ty][tx] = pix;
        }
    }
}

void render(vector<vector<pixel>> &scv , long long mx , long long my ){
    long long center_x = scv[0].size()/2;
    long long center_y = scv.size()/2;
    for(auto &val:chunker){
        chaper(scv , val.second.chunk , val.second.x - mx +center_x, val.second.y - my+center_y);
    }
}

bool is_chunk_loaded(long long x, long long y) {
    return(chunker.count({x,y}));
}

void manage_chunks(long long px, long long py) {
    chunk_unloader(px, py);
    long long gx = floor(px / chunk_size)*chunk_size;
    long long gy = floor(py / chunk_size)*chunk_size;
    for (long long x=gx-render_distance;x<=gx+render_distance;x+=chunk_size)for (long long y = gy - render_distance; y <= gy + render_distance; y +=chunk_size)if (!is_chunk_loaded(x, y))chunk_loader(x, y);
}

int get_block(long long x, long long y){
    long long lx = (x >= 0) ? (x / chunk_size) * chunk_size : ((x - chunk_size + 1) / chunk_size) * chunk_size;
    long long ly = (y >= 0) ? (y / chunk_size) * chunk_size : ((y - chunk_size + 1) / chunk_size) * chunk_size;
    if (!is_chunk_loaded(lx, ly))chunk_loader(lx, ly);
    return chunker[{lx , ly}].chunk[y-ly][x - lx];
}
