#include "output.h"
#include <iostream>

void soft_clear(){
    std::cout << "\033[H";
}

void hard_clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}