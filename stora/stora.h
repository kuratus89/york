#ifndef STORA_H
#define STORA_H

#include "../lib.h"
template<typename T>
bool write_bin(ofstream &out ,const T& v){
    out.write(reinterpret_cast<const char*>(&v) , sizeof(T));
    return out.good();
}
template <typename T>
bool read_bin(ifstream &in , T& v){
    in.read(reinterpret_cast<char*>(&v) , sizeof(T));
    return in.good();
}
bool write_string(ofstream &out , const string &s);
bool read_string(ifstream &in , string &s);

 //variables 
struct pixel {
    int color;
    string value;
    bool operator==(const pixel& other) const {
        return color == other.color && value == other.value;
    }
};
struct win{
    bool type;// type 1 => full window , type 0 => partial window
    string name;// window name
    // data
    map<string , string> sts;
    map<string , long long> stl;
    // map<long long , string> lts;
    // map<long long , long long> ltl;
    map<string , vector<vector<pixel>>> screen;
    map<string ,vector<string>> vs;
    bool initilizzed=0;
    bool screen_handle=0;
    bool adv=0;
    
};
struct boot_data{
    map<string , string> sts;
    map<string , long long> stl;
};

struct mob{
    int id;
    int x;
    int y;
    int health;
    int type;
    int initilize=0;
    int movement_delay=0;
    pair<long long , int> bfs;
    int in_range=0;
    queue<pair<pair<int ,int> , int>> hit;
    int color=-1;
    int delay_color=0;
    map<string , int> stl;
    map<string , string> sts;
    bool save(ofstream &out){
        uint64_t cnt = stl.size();
        write_bin(out , cnt);
        for(auto val:stl){
            write_string(out  , val.first);
            write_bin(out , val.second);
        }

        cnt = sts.size();
        write_bin(out , cnt);
        for(auto val:sts){
            write_string(out , val.first);
            write_string(out , val.second);
        }

        return (write_bin(out , id)&&write_bin(out , x)&&write_bin(out , y)&&write_bin(out , health)&&write_bin(out , type)&&write_bin(out , initilize)&&write_bin(out , bfs.first)&&write_bin(out , bfs.second)&&write_bin(out , in_range));
    }
    bool load(ifstream &in){
        uint64_t cnt;
        read_bin(in , cnt);
        for(int i=0 ; i<cnt ; i++){
            string a;
            int b;
            read_string(in , a);
            read_bin(in , b);
            stl[a]=b;
        }

        read_bin(in , cnt);

        for(int i=0 ; i<cnt ; i++){
            string a;
            string b;
            read_string(in ,a);
            read_string(in , b);
            sts[a]=b;
        }

        return(read_bin(in , id)&&read_bin(in , x)&&read_bin(in , y)&&read_bin(in , health)&&read_bin(in , type)&&read_bin(in , initilize)&&read_bin(in , bfs.first)&&read_bin(in , bfs.second)&&read_bin(in , in_range));
    }
    void spawn(int x , int y,int type){

    }
};

struct chunks{
    int x;
    int y;
    bool always_load=0;
    bool chunk_genrated=0;
    bool struct_genrated=0;
    vector<vector<int>> chunk = vector<vector<int>> (10 , vector<int> (10));
    map<pair<int , int> , int> change;
    vector<mob> mobs;
    bool save(ofstream &out){
        write_bin(out , x);
        write_bin(out , y);
        write_bin(out , always_load);
        write_bin(out , chunk_genrated);
        write_bin(out , struct_genrated);

        uint64_t cnt = change.size();
        write_bin(out , cnt);
        for(auto &[pos,val]:change){
            write_bin(out , pos.first);
            write_bin(out , pos.second);
            write_bin(out , val);
        }

        cnt = mobs.size();
        write_bin(out , cnt);
        for(auto &val :mobs){
            val.save(out);
        }

        return out.good();
    }

    bool load(ifstream& in){
        read_bin(in , x);
        read_bin(in , y);
        read_bin(in , always_load);
        read_bin(in , chunk_genrated);
        read_bin(in , struct_genrated);

        uint64_t cnt;
        read_bin(in , cnt);
        change.clear();
        for(uint64_t i=0 ; i<cnt; i++){
            int xx ,yy,val;
            read_bin(in ,xx);
            read_bin(in , yy);
            read_bin(in , val);
            change[{xx,yy}]= val;
        }
        read_bin(in , cnt);
        mobs.clear();
        mobs.resize(cnt);
        for(auto &val:mobs){
            val.load(in);
        }

        return in.good();
    }
};

struct world{
    string name;
    int seed;
    int posx;
    int posy;
    int health;
    map<pair<int,int>  , chunks> chunker;
    map<int,int> inventory;
 
    map<string,string> sts;
    map<string , long long> stl;
    map<string , int> skill;
    map<string , map<string , int>> inventory_str = {
        {"block", 
            {
                {"air",0},
                {"grass" , 1},
                {"stone" , 2},
                {"iron" , 3},
                {"gold" , 4},
                {"diamond" ,5}
            }
        },
        {"item",
            {
                {"heal" ,6}
            }
        },
        {"weapon",
            {
                {"pistol" , 7},
                {"rifle" , 8}
            }
        },
        {"ammo",
            {
                {"pistol" , 9},
                {"rifle" , 10}
            }
        }
    };
    
    int get_inv(string type , string name){
        return(inventory[inventory_str[type][name]]);
    }

    void set_inv(string type , string name , int n){
        inventory[inventory_str[type][name]] = n;
    }
    void add_inv(string type , string name , int n){
        inventory[inventory_str[type][name]]+=n;
    }

    bool save(const string& file){
        ofstream out(file , ios::binary);
        if(!out)return 0;

        write_string(out , name);
        write_bin(out , seed);
        
        write_bin(out , posx);
        write_bin(out , posy);
        write_bin(out , health);

        uint64_t cnt = chunker.size();
        write_bin(out , cnt);

        for(auto& [pos , val]:chunker){
            write_bin(out , pos.first);
            write_bin(out , pos.second);
            val.save(out);
        }
        cnt = inventory.size();
        write_bin(out , cnt);
        for(auto &val:inventory){
            write_bin(out , val.first);
            write_bin(out , val.second);
        }

        cnt = sts.size();
        write_bin(out , cnt);
        for(auto &val:sts){
            write_string(out , val.first);
            write_string(out , val.second);
        }

        cnt = stl.size();
        write_bin(out , cnt);
        for(auto &val:stl){
            write_string(out , val.first);
            write_bin(out , val.second);
        }

        cnt = skill.size();
        write_bin(out , cnt);
        for(auto &val:skill){
            write_string(out , val.first);
            write_bin(out , val.second);
        }

        return out.good();
    }

    bool load(const string& file){
        ifstream in(file , ios::binary);
        if(!in) return 0;

        read_string(in , name);
        read_bin(in , seed);
        read_bin(in , posx);
        read_bin(in , posy);
        read_bin(in  , health);

        uint64_t cnt;
        read_bin(in , cnt);

        chunker.clear();
        for(uint64_t i= 0 ; i<cnt; i++){
            int xx,yy;
            read_bin(in , xx);
            read_bin(in , yy);

            chunker[{xx,yy}].load(in);
        }
        read_bin(in , cnt);
        inventory.clear();
        for(uint64_t i=0 ; i<cnt ; i++){
            int xx,yy;
            read_bin(in , xx);
            read_bin(in , yy);
            inventory[xx]=yy;
            
        }
        sts.clear();
        read_bin(in , cnt);
        for(uint64_t i = 0 ; i <cnt ; i++){
            string a,b;
            read_string(in , a);
            read_string(in , b);
            sts[a]=b;
        }
        stl.clear();
        read_bin(in , cnt);
        for(uint64_t i=0; i<cnt ; i++){
            string a;long long b;
            read_string(in , a);
            read_bin(in , b);
            stl[a]=b;
        }

        skill.clear();
        read_bin(in , cnt);

        for(int i=0 ; i<cnt ; i++){
            string a;int b;
            read_string(in , a);
            read_bin(in , b);
            skill[a] = b;
        }

        return in.good();
    }
};
bool save_boot_data(const boot_data &data, const std::string &valo, const std::string &dgm);
bool load_boot_data(const string &valo, const string &dgm, boot_data &out_data);
extern bool gameon;
extern stack<win> wino;
extern bool first_boot;
extern string k;
extern map<string , string> string_to_color;
extern vector<string> in_to_color;
extern long long x,y;
extern bool hc;
extern bool ch;
extern bool boot_log;
extern int cx;
extern int cy;
extern char player;
// extern vector<vector<pair<char , char>>> screen;
extern vector<vector<pixel>> pre_screen;
extern int player_color;
extern vector<string> intro_dialog;
extern vector<wstring> title;
extern vector<vector<vector<pixel>>> titles;
extern string player_name;
extern bool speed;
extern bool ghost;
extern vector<pair<int , win>> ticker;
extern long long block_update;
extern int hit_delay;
extern bool show_fps;
extern bool show_latency;
extern double ms;
extern double avg_ms;
extern int target_fps;
extern long long tick;
extern map<string , string> skill_desc;
extern int max_health;
extern int max_break_block;
extern int max_pistol_range;
extern int pistol_gap;

//func


bool isf();




#endif