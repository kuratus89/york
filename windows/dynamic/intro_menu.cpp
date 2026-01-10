
#include "../window.h"
#include "../../stora/stora.h"
#include "../../output/output.h"
#include "input_str.h"
#include "../../stora/stora.h"

long long lx=40;
long long ly=5;
char cha;
vector<string> opt = {
    "input_str",
    "input_str",
    "hululu" 
} ;
vector<string> options = {
    "  EDIT NAME",
    "  EDIT CHARACTER",
    "  DONE"
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
            cl.push_back(']');
            for(auto val:cl){
                valo[gy][gx] = {colo , val};
                gx++;
            }
        }
        if(i==1){
            string cl = "[CURRENT CHARACTER->";
            cl.push_back(cha);
            cl.push_back(']');
            for(auto val:cl){
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
    else if(k=="W")selecter--;
    if(selecter<0)selecter =options.size()-1; 
    if(selecter>options.size()-1)selecter=0;
    if(k=="Enter"){
        // cout<<"hulululu";
        win ed;
        ed.name = opt[selecter];
        if(selecter==0){
            ed.sts["value"]="NAME";
            ed.sts["api"]="name";
            ed.stl["limit"]=7;
            wino.push(ed);
        }
        else if(selecter==1){
            ed.sts["value"]="character";
            ed.sts["api"]="player_cha";
            ed.stl["limit"]=1;
            wino.push(ed);
        }
        else if(selecter == 2){
            if(wino.top().sts["name"]==""){
                ed.name = "msg";
                ed.sts["title"]="name?";
                ed.vs["msg"] = {"Please enter name"};
                ed.sts["color"]="0";
                wino.push(ed);
            }
            else {
                boot_data bd;
                bd.stl["x"]=x;
                bd.stl["y"]=y;
                bd.sts["name"]=wino.top().sts["name"];
                bd.sts["character"]=cha;
                if(save_boot_data(bd , "data" , "boot.kp")){
                    wino.pop();
                    wino.top().stl["done"]=1;
                }
                else {
                    ovr("cant save files");
                }
            }
        }
    }
}
void clr(char colo){
    for(long long i=1 ; i<ly-1 ; i++){
        for(long long j=1; j<lx-1 ; j++){
            wino.top().screen["par_screen"][i][j]= {colo , ' '};
        }
    }
}

void intro_menu(){
    auto &gura = wino.top();
    if(!gura.initilizzed){
        gura.initilizzed=1;
        gura.type=1;
        cha='@';
        gura.screen["screen"] = pre_screen;
        gura.screen["par_screen"] = bod_create('5' , lx , ly);
        gura.screen_handle=1;
        string title = "ENTER DETAILS";
        gura.sts["name"]="";
        long long lox= (max(0LL,lx-(long long)title.size()-2)/2)+1;
        for(auto &val:title){
            if(lox>=gura.screen["par_screen"][0].size()-1)break;
            gura.screen["par_screen"][0][lox]={'5',val};
            lox++;
        }
    }
    if(gura.sts["player_cha"]!="")cha = gura.sts["player_cha"][0];
    clr('5');
    
    opt_adder(gura.screen["par_screen"] ,'5');
    par_scr(gura.screen["screen"] , gura.screen["par_screen"] , 3 , 3);
    optin();

}