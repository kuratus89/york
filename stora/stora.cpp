
// store data and controls read/write of files system *_*

#include "stora.h"
#include "bits/stdc++.h"
#include <filesystem>
#include "../windows/window.h"
using namespace std;
namespace fs = std::filesystem;

// variables
long long x = 10;
long long y = 5;
long long xmin=8;
long long ymin=4;
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

bool hc=0; // need to hard clear?
bool ch=1; // change happen?


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

void save_sts(const map<string,string>& mp, const string& filename) {
    ofstream out(filename);
    for (auto& [key, value] : mp) {
        out << key << "=" << value << "\n";
    }
}

bool isf(){
    string target = "data/boot.kp";
    for (const auto& entry : fs::recursive_directory_iterator("data")) {
        if (entry.path().filename() == target) {
            return 1;
        }
    }

    return 0;
}
