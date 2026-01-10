
#include "../lib.h"
#include "../stora/stora.h"

bool isbo(){
    return(cy==y-6);
}

void delay(long long v){
    this_thread::sleep_for(std::chrono::milliseconds(v));
}