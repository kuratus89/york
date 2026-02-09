
#include "../lib.h"
#include "chunk.h"
#include "core.h"
#include "../stora/stora.h"
#include "../windows/error.h"
#include "npc.h"

long long grass_lvl=10;
// vector<chunks> chunker;
map<pair<int , int> , chunks> chunker;
long long render_distance = 120;
vector<pair<string , pair<string, int>>> blocker = {
    {"air",{" " , 5}},//0
    {"grass",{"█",2}},//1
    {"stone" , {"█" , 6}},//2
    {"iron" , {"█" , 7}},//3
    {"gold" , {"█" , 8}},//4
    {"diamond" , {"█" , 4}}//5
};
vector<pair<string , pair<string , int>>> mober ={
    {"sheep" , {"S" , 5}},
    {"zombie" , {"Z" , 2}}
};
long long chunk_size = 10;
world ear;
long long mob_count=15;
mob player_haha;
mob none;

void chunk_loader(long long  lcx ,long long lcy){
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
            if(is_iron(lcx+i,lcy+j))jk.chunk[j][i]=3;
            if(is_gold(i+lcx,j+lcy))jk.chunk[j][i]=4;
            if(is_diamond(i+lcx,j+lcy))jk.chunk[j][i]=5;
        }
    }
    if(ear.chunker[{lcx , lcy}].change.size())jk.change = ear.chunker[{lcx , lcy}].change;
    if(ear.chunker[{lcx , lcy}].mobs.size())jk.mobs = ear.chunker[{lcx , lcy}].mobs;
    for(auto &val:jk.change){
            jk.chunk[val.first.second][val.first.first] = val.second;
    }
    
    int spawn_height = height(lcx+5)-1;
    if(((spawn_height>=lcy)&&spawn_height<lcy+chunk_size)&&(ear.stl["mobs_count"]<mob_count&&(abs(lcx)>100))){
        mob b;
        b.type=1;
        b.x = lcx+5;
        b.y = height(lcx+5)-1;
        ear.stl["mobs_count"]++;
        jk.mobs.push_back(b);
    }
    chunker[{lcx,lcy}] = (jk);

}
void chunk_unloader(long long lvx , long long lvy){
    
    

    for(auto it = chunker.begin() ; it!=chunker.end() ;){
        if((abs((*it).second.x - lvx)>render_distance)||((abs((*it).second.y - lvy)>render_distance))){
            // ear.stl["mobs_count"]-= chunker[(*it).first].mobs.size();
            ear.chunker[(*it).first].change = (*it).second.change;
            ear.chunker[(*it).first].mobs = (*it).second.mobs;
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

void mob_render(vector<vector<pixel>> &scv , mob moho , long long hx , long long hy){
    if(hx< 0 || hx >= scv[0].size()) return;
    if(hy< 0 || hy >= scv.size()) return;
    if(moho.color==-1)scv[hy][hx].color = mober[moho.type].second.second;
    else scv[hy][hx].color = moho.color;
    scv[hy][hx].value = mober[moho.type].second.first;
}

void render(vector<vector<pixel>> &scv , long long mx , long long my ){
    long long center_x = scv[0].size()/2;
    long long center_y = scv.size()/2;
    for(auto &val:chunker){
        chaper(scv , val.second.chunk , val.second.x - mx +center_x, val.second.y - my+center_y);
        for(auto &var:val.second.mobs)mob_render(scv , var , var.x - mx+center_x , var.y - my + center_y);
    }
}

bool is_chunk_loaded(long long x, long long y) {
    return(chunker.count({x,y}));
}

void manage_chunks(long long px, long long py) {
    chunk_unloader(px, py);
    // long long gx = floor(px / chunk_size)*chunk_size;
    // long long gy = floor(py / chunk_size)*chunk_size;
    long long gx = (px >= 0) ? (px / chunk_size) * chunk_size : ((px - chunk_size + 1) / chunk_size) * chunk_size;
    long long gy = (py >= 0) ? (py / chunk_size) * chunk_size : ((py - chunk_size + 1) / chunk_size) * chunk_size;
    
    for (long long x=gx-render_distance;x<=gx+render_distance;x+=chunk_size)for (long long y = gy - render_distance; y <= gy + render_distance; y +=chunk_size)if (!is_chunk_loaded(x, y))chunk_loader(x, y);
}

int get_block(long long x, long long y){
    long long lx = (x >= 0) ? (x / chunk_size) * chunk_size : ((x - chunk_size + 1) / chunk_size) * chunk_size;
    long long ly = (y >= 0) ? (y / chunk_size) * chunk_size : ((y - chunk_size + 1) / chunk_size) * chunk_size;
    // long long lx = floor(x / chunk_size)*chunk_size;
    // long long ly = floor(y / chunk_size)*chunk_size;
    
    if (!is_chunk_loaded(lx, ly))chunk_loader(lx, ly);
    return chunker[{lx , ly}].chunk[y-ly][x - lx];
}

int get_mob(long long x , long long y){
    if((x==cx)&&(y==cy))return -395;
    long long lx = (x>=0)?(x/chunk_size)*chunk_size : ((x-chunk_size +1)/ chunk_size)*chunk_size;
    long long ly = (y>=0)?(y/chunk_size)*chunk_size : ((y-chunk_size+1)/chunk_size)*chunk_size;
    if(!is_chunk_loaded(lx , ly))chunk_loader(lx , ly);
    for(auto &val:chunker[{lx,ly}].mobs){
        if((val.x==x)&&(val.y==y))return val.type;
    }
    return -1;
}
mob& get_mob_id(long long x , long long y){
    if((x==cx)&&(y==cy)){
        player_haha.health = -395;
        return player_haha;
    }
    long long lx = (x>=0)?(x/chunk_size)*chunk_size : ((x - chunk_size+1)/chunk_size)*chunk_size;
    long long ly = (y>=0)?(y/chunk_size)*chunk_size : ((y - chunk_size+1 )/chunk_size)*chunk_size;
    if(!is_chunk_loaded(lx ,ly))chunk_loader(lx , ly);
    for(auto &val:chunker[{lx , ly}].mobs){
        if((val.x==x)&&(val.y==y))return val;
    }
    none.health=-1;
    return none;
}

void set_block(long long x, long long y , int d){
    long long lx;
    if(x>=0)lx = (x/chunk_size)*chunk_size;
    else lx = ((x - chunk_size+1)/chunk_size)*chunk_size;
    long long ly ;
    if(y>=0) ly = (y/chunk_size)*chunk_size;
    else ly = ((y -chunk_size+1)/chunk_size)*chunk_size;
    if(!is_chunk_loaded(lx , ly)){
        crash("trying to modify unloaded chunk");
        return;
    }
    chunker[{lx , ly}].chunk[y - ly][x - lx] = d;
    chunker[{lx , ly}].change[{x - lx , y - ly}] = d;
    block_update++;
}

bool save_game(string s){
    ear.posx = cx;
    ear.posy = cy;
    for(auto it = chunker.begin() ; it!=chunker.end() ;it++){
        ear.chunker[(*it).first].change = (*it).second.change;
    }
    return ear.save(s);
}

void manage_all_mobs(){
    queue<pair<pair<long long , long long>, mob>> mob_transfer;
    queue<pair<long long , long long>> chunk_loader_queue;
    queue<mob*> mob_manage;
    for(auto &val:chunker){
        for(auto it = val.second.mobs.begin() ; it!=val.second.mobs.end() ;){
            
            long long lx =  ((*it).x>=0)?((*it).x/chunk_size)*chunk_size : (((*it).x-chunk_size +1)/chunk_size)*chunk_size;
            long long ly = ((*it).y>=0)? ((*it).y/chunk_size)*chunk_size : (((*it).y - chunk_size+1)/chunk_size)*chunk_size;
            if((val.first.first!=lx)||(val.first.second!=ly)){
                if(!is_chunk_loaded(lx , ly))chunk_loader_queue.push({lx , ly});
                mob_transfer.push({{lx,ly} , (*it)});
                it = val.second.mobs.erase(it);
            }
            else if((*it).health<=0){
                it = val.second.mobs.erase(it);
            }
            else {
                mob_manage.push(&(*it));
                it++;
            }
        }
    }
    while(!chunk_loader_queue.empty()){
        chunk_loader(chunk_loader_queue.front().first , chunk_loader_queue.front().second);
        chunk_loader_queue.pop();
    }
    while(!mob_manage.empty()){
        mob_manager(*mob_manage.front());
        mob_manage.pop();
    }
    while(!mob_transfer.empty()){
        chunker[mob_transfer.front().first].mobs.push_back(mob_transfer.front().second);
        mob_transfer.pop();
    }
    
}
