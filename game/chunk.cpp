
#include "../lib.h"
#include "chunk.h"
#include "core.h"
#include "../stora/stora.h"
#include "../windows/error.h"
#include "npc.h"
#include "../struct/struct.h"

long long grass_lvl=10;
// vector<chunks> chunker;
map<pair<int , int> , chunks> chunker;
long long render_distance = 120;
long long mobs_per_chunk=2;

vector<pair<string , pair<string, int>>> blocker = {
    {"air",{" " , 5}},//0
    {"grass",{"█",2}},//1
    {"stone" , {"█" , 6}},//2
    {"iron" , {"█" , 7}},//3
    {"gold" , {"█" , 8}},//4
    {"diamond" ,  {"█" , 4}},//5
    {"struct_1" , {"▓", 0}},//6
    {"struct_2" , {"▒",0}},//7
    {"struct_3" , {"░" , 0}},//8
};
vector<pair<string , pair<string , int>>> mober ={
    {"sheep" , {"S" , 5}},
    {"zombie" , {"Z" , 2}},
    {"bullet" , {"-" , 5}},
    {"loot" , {"*" , 5}},
    {"grave" , {"*" , 5}},
    {"bures" , {"H" , 5}},
    {"kures_mob" , {"▪",5}},
    {"kuers" , {"▪" , 5}},

};
long long chunk_size = 10;
world ear;
long long mob_count=150;
mob none;

int chunk_cor(int i){
    if(i>=0)return ((i/chunk_size)*chunk_size);
    else return (((i - chunk_size +1)/chunk_size)*chunk_size);
}

void load_mobs(int lcx , int lcy){
    auto it = &chunker[{lcx , lcy}];
    if(it->mobs.size()>mobs_per_chunk)return;
    int local_mob_count = mobs_per_chunk;
    if(ear.chunker[{lcx , lcy}].mobs.size()){
        (*it).mobs = ear.chunker[{lcx, lcy}].mobs;
        ear.stl["mob_count"]+=ear.chunker[{lcx , lcy}].mobs.size();
        local_mob_count = max(0 , local_mob_count - (int)(*it).mobs.size());
    }
    

    for(int i=0 ; (i<chunk_size)&&(local_mob_count>0) ; i++){
        int h = height(lcx +i);
        int g = grass(lcx+i);

        for(int j=0 ; ((j<chunk_size -1)&&(local_mob_count>0)&&(ear.stl["mob_count"]<mob_count)) ; j++){
            int wx = lcx +i;
            int wy = lcy+j;

            if(wy<h)continue;
            if(get_block(wx , wy)||(!get_block(wx , wy+1)))continue;

            int type;
            if(wy<=g+3)type = 0;
            else type = 1;

            if(rand()%120)continue;

            spawn(wx , wy , type , it);
            ear.stl["mob_count"]++;
            local_mob_count--;
        }
    }

}


void spawn_mob(int lx , int ly , int type){

    // auto it = &chunker[{lx , ly}];
    auto it = chunk_pointer(lx , ly);

    spawn(lx , ly , type , it);

}





void struct_genrator(int x , int y){
    if(y<=height(x))return;
    if(ear.chunker[{x,y}].struct_genrated)return;

    for(int j=0 ; j<chunk_size ; j++){
        for(int i=0 ; i<chunk_size ; i++){
            if(!has_struct(x+i , y+j))continue;

            spawn_struct(struct_selecter(y) , x+i , y+j);
            ear.chunker[{x,y}].struct_genrated=1;
        }
    }
}


void chunk_loader(long long  lcx ,long long lcy){
    chunks jk;
    jk.x = lcx;
    jk.y = lcy;
    
    int mob_per_chunk_count = max(0LL , mobs_per_chunk- (long long)jk.mobs.size());
    for(long long i=0 ; i<10; i++){
        long long h = height(lcx+i);
        long long g = grass(lcx +i);
        for(long long j=0 ; j<10 ; j++){
            if(lcy+j<h){
                jk.chunk[j][i]=0;
                continue;
            }
            else if(is_air(lcx+i , lcy+j)){
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
    for(auto &val:jk.change){
            jk.chunk[val.first.second][val.first.first] = val.second;
    }    
    chunker[{lcx,lcy}] = (jk);

    struct_genrator(lcx , lcy);
    load_mobs(lcx , lcy);    

}

void chunk_unloader(long long lvx , long long lvy){
    for(auto it = chunker.begin() ; it!=chunker.end() ;){
        if((abs((*it).second.x - lvx)>render_distance)||((abs((*it).second.y - lvy)>render_distance))){
            // ear.stl["mobs_count"]-= chunker[(*it).first].mobs.size();
            ear.chunker[(*it).first].change = (*it).second.change;
            ear.chunker[(*it).first].mobs = (*it).second.mobs;
            ear.stl["mob_count"]-= (*it).second.mobs.size();
            it = chunker.erase(it);
        }
        else it++;
    }
}

void chaper(vector<vector<pixel>> &scv , vector<vector<int>> &chk , long long vx , long long vy){
    for(long long i = 0; i < chk[0].size(); ++i){
        long long tx = vx + i;
        if(tx < 0 || tx >= scv[0].size()) continue;

        for(long long j = 0; j < chk.size(); ++j){
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
    if(moho.sts.count("render")&&moho.sts["render"]!="")scv[hy][hx].value = moho.sts["render"];
    else scv[hy][hx].value = mober[moho.type].second.first;
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


void manage_chunks(int x , int y){
    chunk_unloader(x ,y);
    int lx = chunk_cor(x);
    int ly = chunk_cor(y);
    for(int j = lx - render_distance ; j<=lx+render_distance ; j+=chunk_size){
        for(int i = ly - render_distance ; i<= ly+render_distance ; i+=chunk_size){
            if(is_chunk_loaded(j,i))continue;
            chunk_loader(j , i);
        }
    }
}



int get_block(int x , int y){
    int lx = chunk_cor(x);
    int ly = chunk_cor(y);
    if(!is_chunk_loaded(lx , ly))chunk_loader(lx , ly);
    return chunker[{lx , ly}].chunk[y- ly][x - lx];
}


int get_mob(int x , int y){
    if((x==cx)&&(y==cy))return -395;
    int lx = chunk_cor(x);
    int ly = chunk_cor(y);
    if(!is_chunk_loaded(lx , ly))chunk_loader(lx , ly);
    for(auto &val:chunker[{lx , ly}].mobs)if((val.x==x)&&(val.y==y))return val.type;
    return -1;
}

mob& get_mob_id(int x , int y){
    if((x==cx)&&(y==cy)){
        none.health = -395;
        return none;
    }
    int lx = chunk_cor(x);
    int ly = chunk_cor(y);
    if(!is_chunk_loaded(lx , ly))chunk_loader(lx , ly);
    for(auto &val:chunker[{lx , ly}].mobs)if((val.x==x)&&(val.y==y))return val;
    none.health = -1;
    return none;
}


void set_block(int x , int y , int block){
    int bx = chunk_cor(x);
    int by = chunk_cor(y);

    if(!is_chunk_loaded(bx , by))chunk_loader(bx , by);
    chunker[{bx , by}].chunk[y - by][x - bx] = block;
    chunker[{bx , by}].change[{x - bx , y - by}]= block;
}

chunks* chunk_pointer(int bx , int by){
    int lx = chunk_cor(bx);
    int ly = chunk_cor(by);
    if(!is_chunk_loaded(lx , ly))chunk_loader(lx , ly);
    return &chunker[{lx , ly}];
}


bool save_game(string s){
    ear.posx = cx;
    ear.posy = cy;
    for(auto it = chunker.begin() ; it!=chunker.end() ;it++){
        ear.chunker[(*it).first].change = (*it).second.change;
    }
    return ear.save(s);
}

void manage_all_mobs(vector<vector<pixel>> &scr){
    queue<pair<pair<int , int> , mob>> mob_transfer;
    queue<pair<int , int>> chunk_loader_queue;
    queue<mob*> mob_manage;
    bool boss_mob=0;
    for(auto &val:chunker){
        for(auto it = val.second.mobs.begin() ; it!=val.second.mobs.end();){
            int lx = chunk_cor((*it).x);
            int ly = chunk_cor ((*it).y);
            if((val.first.first!=lx)||(val.first.second!=ly)){
                if(!is_chunk_loaded(lx , ly))chunk_loader_queue.push({lx , ly});
                mob_transfer.push({{lx , ly} , (*it)});
                it = val.second.mobs.erase(it);
            }
            else if((*it).health<=0){
                if(((*it).type!=4)&&(!(*it).kill_reward.empty())){
                    mob mo;
                    mo.type = 4;
                    mo.kill_reward = (*it).kill_reward;
                    mo.x = (*it).x;
                    mo.y = (*it).y;
                    mob_transfer.push({{lx , ly} , mo});
                }
                it = val.second.mobs.erase(it);
                ear.stl["mob_count"]--;
            }
            else {
                if((it->stl["boss"])&&(!boss_mob)){
                    boss_title(scr , (*it));
                    boss_mob=0;
                }
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