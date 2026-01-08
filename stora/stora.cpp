
// store data and controls read/write of files system *_*

#include "stora.h"
#include "../lib.h"
#include "../windows/window.h"
#include "../output/output.h"
using namespace std;
namespace fs = std::filesystem;

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
long long cx,cy;
char player;
string player_color;
vector<string> intro_dialog = {
    "Hi, Spatial-oh, you seem confused by that word ,so let me explain: you are a tri-dimensional organism, and that's why I call you Spatial.",
    "As I promised, I surrender my will to you-but in return, you must make me York; and because a world can endure only one York, you will have to erase the one who exists now.",
    "Strip me of my old name and grant me a new one-and if it pleases you, reshape my very appearance as well."
};

// functions


void load_sts(string path, map<string, string>& m) {
    ifstream file(path);
    if (!file.is_open()) return;
    string key, value;
    while (file >> key >> value) {
        m[key] = value;
    }
    file.close();
}

void save_sts(string path, map<string, string>& m) {
    ofstream file(path);
    if (!file.is_open()) return;
    for (auto& pair : m) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
}

void load_stl(string path, map<string, long long>& m) {
    ifstream file(path);
    if (!file.is_open()) return;
    string key;
    long long value;
    while (file >> key >> value) {
        m[key] = value;
    }
    file.close();
}

void save_stl(string path, map<string, long long>& m) {
    ofstream file(path);
    if (!file.is_open()) return;
    for (auto& pair : m) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
}

void load_lts(string path, map<long long, string>& m) {
    ifstream file(path);
    if (!file.is_open()) return;
    long long key;
    string value;
    while (file >> key >> value) {
        m[key] = value;
    }
    file.close();
}

void save_lts(string path, map<long long, string>& m) {
    ofstream file(path);
    if (!file.is_open()) return;
    for (auto& pair : m) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
}

void load_ltl(string path, map<long long, long long>& m) {
    ifstream file(path);
    if (!file.is_open()) return;
    long long key, value;
    while (file >> key >> value) {
        m[key] = value;
    }
    file.close();
}

void save_ltl(string path, map<long long, long long>& m) {
    ofstream file(path);
    if (!file.is_open()) return;
    for (auto& pair : m) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
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