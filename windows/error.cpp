
#include "error.h"
#include "../output/output.h"
#include "../stora/stora.h"
#include "../lib.h"

void error(){
    hard_clear();
    cout<<"sorry but the game crash >_<"<<endl;
    cout<<"reason => ";
    cout<<wino.top().sts["value"];

}