
// store data and controls read/write of files system *_*

#include "stora.h"
#include "../lib.h"
#include "../windows/window.h"
#include "../output/output.h"
using namespace std;
namespace fs = filesystem;

// variables
long long x = 60;
long long y = 20;
long long xmin=15;
long long ymin=8;
long long ymax=LLONG_MAX;
long long xmax=LLONG_MAX;
long long rx=50; //recommended x and y
long long ry = 15;
bool gameon=1;
string k="-";
stack<win> wino;
bool first_boot=1;
map<string , string> string_to_color={
    {"red","\033[31m"},
    {"blue" ,"\033[34m"},
    {"green" , "\033[32m"},
    {"purple" , "\033[35m"},
    {"cyan" , "\033[36m"},
    {"white" , "\033[37m"},
    {"reset" , "\033[0m"}
};
vector<string> in_to_color = {"\033[31m" ,"\033[34m","\033[32m","\033[35m","\033[36m","\033[37m","\033[0m"};

bool hc=1; // need to hard clear?
bool ch=1; // change happen?
bool boot_log =1;
// vector<vector<pair<char , char>>> screen;
vector<vector<pair<char , char>>> pre_screen;
long long cx=3,cy=1;

char player;
char player_color='5';
char title_color = '4';
vector<string> intro_dialog = {
    "Hi, Spatial-oh, you seem confused by that word ,so let me explain: you are a tri-dimensional organism, and that's why I call you Spatial.",
    "As I promised, I surrender my will to you-but in return, you must make me York; and because a world can endure only one York, you will have to erase the one who exists now.",
    "Strip me of my old name and grant me a new one-and if it pleases you, reshape my very appearance as well."
};

std::vector<std::vector<std::pair<char, char>>> title = {
    { {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'.'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'s'}, {title_color,'S'}, {title_color,'S'}, {title_color,'s'}, {title_color,'_'}, {title_color,'s'}, {title_color,'S'}, {title_color,'S'}, {title_color,'s'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'_'}, {title_color,'s'}, {title_color,'S'}, {title_color,'S'}, {title_color,'s'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'.'}, {title_color,' '}, {title_color,' '}, {title_color,' '} },
    { {title_color,'.'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,'.'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'d'}, {title_color,'%'}, {title_color,'%'}, {title_color,'S'}, {title_color,'P'}, {title_color,'~'}, {title_color,'Y'}, {title_color,'S'}, {title_color,'%'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'S'}, {title_color,'~'}, {title_color,'Y'}, {title_color,'S'}, {title_color,'%'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,'.'}, {title_color,' '}, {title_color,' '} },
    { {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'d'}, {title_color,'%'}, {title_color,'S'}, {title_color,'\''}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'`'}, {title_color,'S'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'`'}, {title_color,'S'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '} },
    { {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'d'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '} },
    { {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'d'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,'_'}, {title_color,'s'}, {title_color,'d'}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,' '}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,'_'}, {title_color,'s'}, {title_color,'d'}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,'~'}, {title_color,'Y'}, {title_color,'S'}, {title_color,'S'}, {title_color,'Y'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,'~'}, {title_color,'Y'}, {title_color,'S'}, {title_color,'Y'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'`'}, {title_color,'S'}, {title_color,'%'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'d'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'`'}, {title_color,'S'}, {title_color,'%'}, {title_color,'b'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,'.'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'.'}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'%'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,'b'}, {title_color,'s'}, {title_color,'_'}, {title_color,'s'}, {title_color,'d'}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'&'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'Y'}, {title_color,'S'}, {title_color,'S'}, {title_color,'P'}, {title_color,'~'}, {title_color,'Y'}, {title_color,'S'}, {title_color,'S'}, {title_color,'Y'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'*'}, {title_color,'S'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'S'}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'P'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'P'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'S'}, {title_color,'P'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,'Y'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'Y'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,'Y'}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '} },
    { {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '}, {title_color,' '} },
};

// functions

static bool writeString(ofstream &out, const string &s) {
    uint64_t len = static_cast<uint64_t>(s.size());
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(s.data(), static_cast<streamsize>(len));
    return out.good();
}

static bool readString(ifstream &in, string &s) {
    uint64_t len{};
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!in.good()) return false;
    s.resize(static_cast<size_t>(len));
    in.read(&s[0], static_cast<streamsize>(len));
    return in.good();
}

bool save_boot_data(const boot_data &data, const string &valo, const string &dgm) {
    try {
        fs::path dir = valo;
        fs::create_directories(dir);
        fs::path file = dir / dgm;
        ofstream out(file, ios::binary | ios::trunc);
        if (!out) return false;

        uint64_t sts_size = static_cast<uint64_t>(data.sts.size());
        out.write(reinterpret_cast<const char*>(&sts_size), sizeof(sts_size));
        for (const auto &kv : data.sts) {
            if (!writeString(out, kv.first))  return false;
            if (!writeString(out, kv.second)) return false;
        }

        uint64_t stl_size = static_cast<uint64_t>(data.stl.size());
        out.write(reinterpret_cast<const char*>(&stl_size), sizeof(stl_size));
        for (const auto &kv : data.stl) {
            if (!writeString(out, kv.first)) return false;
            long long v = kv.second;
            out.write(reinterpret_cast<const char*>(&v), sizeof(v));
            if (!out.good()) return false;
        }

        return out.good();
    } catch (...) {
        return false;
    }
}

bool load_boot_data(const string &valo, const string &dgm, boot_data &out_data) {
    try {
        fs::path file = fs::path(valo) / dgm;
        ifstream in(file, ios::binary);
        if (!in) return false;

        boot_data temp;

        uint64_t sts_size{};
        in.read(reinterpret_cast<char*>(&sts_size), sizeof(sts_size));
        if (!in.good()) return false;
        for (uint64_t i = 0; i < sts_size; ++i) {
            string k, v;
            if (!readString(in, k)) return false;
            if (!readString(in, v)) return false;
            temp.sts.emplace(move(k), move(v));
        }

        uint64_t stl_size{};
        in.read(reinterpret_cast<char*>(&stl_size), sizeof(stl_size));
        if (!in.good()) return false;
        for (uint64_t i = 0; i < stl_size; ++i) {
            string k;
            long long v{};
            if (!readString(in, k)) return false;
            in.read(reinterpret_cast<char*>(&v), sizeof(v));
            if (!in.good()) return false;
            temp.stl.emplace(move(k), v);
        }

        out_data = move(temp); // commit
        return true;
    } catch (...) {
        return false;
    }
}

bool isf(){
    string target = "data/boot.kp";
    if (!fs::exists("data")) return 0; // Add this check
    for (const auto& entry : fs::recursive_directory_iterator("data")) {
        if (entry.path().filename() == "boot.kp") { // Also fix the comparison logic here
            return 1;
        }
    }
    return 0;
}