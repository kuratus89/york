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
    bool save(ofstream &out){
        return (write_bin(out , id)&&write_bin(out , x)&&write_bin(out , y)&&write_bin(out , health)&&write_bin(out , type));
    }
    bool load(ifstream &in){
        return(read_bin(in , id)&&read_bin(in , x)&&read_bin(in , y)&&read_bin(in , health)&&read_bin(in , type));
    }
};

struct chunks{
    int x;
    int y;
    bool always_load=0;
    vector<vector<int>> chunk = vector<vector<int>> (10 , vector<int> (10));
    map<pair<int , int> , int> change;
    vector<mob> mobs;
    bool save(ofstream &out){
        write_bin(out , x);
        write_bin(out , y);
        write_bin(out , always_load);

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
    map<pair<int,int>  , chunks> chunker;



    bool save(const string& file){
        ofstream out(file , ios::binary);
        if(!out)return 0;

        write_string(out , name);
        write_bin(out , seed);
        
        write_bin(out , posx);
        write_bin(out , posy);

        uint64_t cnt = chunker.size();
        write_bin(out , cnt);

        for(auto& [pos , val]:chunker){
            write_bin(out , pos.first);
            write_bin(out , pos.second);
            val.save(out);
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

        uint64_t cnt;
        read_bin(in , cnt);

        chunker.clear();
        for(uint64_t i= 0 ; i<cnt; i++){
            int xx,yy;
            read_bin(in , xx);
            read_bin(in , yy);

            chunker[{xx,yy}].load(in);
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
extern long long xmin;
extern long long ymin;
extern long long ymax;
extern long long xmax;
extern bool hc;
extern bool ch;
extern long long rx;
extern long long ry;
extern bool boot_log;
extern long long cx;
extern long long cy;
extern char player;
// extern vector<vector<pair<char , char>>> screen;
extern vector<vector<pixel>> pre_screen;
extern int player_color;
extern vector<string> intro_dialog;
extern vector<wstring> title;
extern vector<vector<vector<pixel>>> titles;

//func


bool isf();




#endif