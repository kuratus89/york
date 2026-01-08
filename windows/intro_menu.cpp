
#include "window.h"
#include "../stora/stora.h"
#include "../output/output.h"



vector<void(*)()> opt ;
vector<string> options = {
    "  EDIT NAME",
    "  EDIT CHARACTER",
    "  START"
};
long long selecter=0;

void opt_adder(vector<vector<pair<char , char>>> &valo , char colo){
    long long gy=1;
    for(long long i=0 ; i<options.size() ; i++ , gy++){
        long long gx=1;
        for(auto val:options[i]){
            valo[gy][gx] = {colo , val};
            gx++;
        }
        if((i==0)&&(wino.top().sts["name"]!="")){
            string cl = "[CURRENT NAME->";
            cl+=wino.top().sts["name"];
            for(auto val:options[i]){
                valo[gy][gx] = {colo , val};
                gx++;
            }
        }
        if(i==selecter){
            valo[gy][1]={colo , '-'};
            valo[gy][2] = {colo , '>'};
        }
    }
}
void optin(){
    if(k=="S")selecter++;
    else if(k=="W")selecter=0;

    if(selecter<0)selecter =options.size()-1; 
    if(selecter>options.size()-1)selecter=0;
}

void intro_menu(){
    auto &gura = wino.top();
    if(!gura.initilizzed){
        gura.initilizzed=1;
        gura.type=1;
        gura.screen = pre_screen;
        gura.par_screen = bod_create('5' , 30 , 5);
        gura.screen_handle=1;
        string title = "ENTER DETAILS";
        gura.sts["name"]="";
        long long lox= (max(0LL,(long long)gura.par_screen[0].size()-(long long)title.size()-2)/2)+1;
        for(auto &val:title){
            if(lox>=gura.par_screen[0].size()-1)break;
            gura.par_screen[0][lox]={'5',val};
            lox++;
        }
    }
    optin();
    opt_adder(gura.par_screen ,'5');
    par_scr(gura.screen , gura.par_screen , 3 , 3);


}