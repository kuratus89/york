
#include "../lib.h"
#include "../stora/stora.h"
#include "../game/chunk.h"
#include "../windows/dynamic/inventory.h"
#include "../game/weapon.h"
#include "../game/npc.h"
#include "../input/input.h"

long long jump_hight = 6;
long long jump_stage = 0;
int break_block=max_break_block;
int target_block_x=-395;
int target_block_y=-395;
bool breaking=0;
int depth_damage_gap=10;
int depth_damage_tick=0;
string fi = "fist";


bool isbo(){
    return(cy==y-6);
}

void delay(long long v){
    if(speed)return;
    this_thread::sleep_for(std::chrono::milliseconds(v));
}
bool is_ground(int &vx , int &vy){
    return(get_block(vx , vy+1));
}


void move_left(int &vx , int &vy){
    if((get_mob(vx-1 , vy)!=-1)&&(get_mob_id(vx-1 , vy).stl["ghost"]==0))return;
    if(((!get_block(vx-1 , vy))||(ghost))){
        if((input::ikd(input::key::Shift))&&(!get_block(vx-1 , vy+1)))return;
        else vx--;
        return;
    }
    if(input::ikd(input::key::Shift))return;
    else if((get_block(vx-1 , vy))&&(!get_block(vx-1 , vy-1))&&(!get_block(vx , vy-1))&&(get_mob(vx-1 , vy-1)==-1)&&(get_mob(vx , vy-1)==-1)){
        vx--;
        vy--;
    }
}


void move_right(int &vx , int &vy){
    if((get_mob(vx +1 , vy)!=-1)&&(get_mob_id(vx+1 , vy).stl["ghost"]==0))return;
    if(((!get_block(vx+1 , vy))||(ghost))){
        if((input::ikd(input::key::Shift))&&(!get_block(vx+1 , vy+1)))return;
        else vx++;
        return;
    }
    if(input::ikd(input::key::Shift))return;
    else if((get_block(vx+1 , vy))&&(!get_block(vx+1 , vy-1)) &&(!get_block(vx , vy-1))&&(get_mob(vx+1 , vy-1)==-1)&&(get_mob(vx , vy-1)==-1)){
        vx++;
        vy--;
    }
}

void move_up(int &vx , int &vy){
    if((get_mob(vx , vy-1)!=-1)&&(get_mob_id(vx , vy-1).stl["ghost"]==0))return;
    if((!get_block(vx , vy-1))||(ghost))vy--;
}
void move_down(int &vx , int &vy){
    if((get_mob(vx , vy+1)!=-1)&&(get_mob_id(vx , vy+1).stl["ghost"]==0))return;
    if((!get_block(vx , vy+1))||(ghost))vy++;
}


void gravity(int &vx , int &vy){
    if(ghost)return;
    if(jump_stage)return;
    if(get_block(vx , vy+1))return;
    if((get_mob(vx , vy+1)==-1)&&(get_mob_id(vx , vy+1).stl["ghost"]==0))vy++;
}
void jump(){
    if(jump_stage)return;
    if(!is_ground(cx , cy))return;
    if((!get_block(cx , cy-1))&&(get_mob(cx , cy-1)==-1)){
        // delay(30);
        cy--;
        jump_stage = 1;
    }
}
// void manage_jump(){
//     jump_stage = jump_stage%jump_hight;
//     if(jump_stage){
//         if(!get_block(cx , cy-1)){
//             cy--;
            
//         }
//         jump_stage++;
//     }
// }
void manage_jump(){
    if(jump_stage > 0){
        if(jump_stage < jump_hight){
            delay(5);
            if(!get_block(cx , cy-1)){
                cy--;
                jump_stage++;
            } else {
                jump_stage = 0;
            }
        } else {
            jump_stage = 0;
        }
    }
}

void block_breaker(int x , int y , map<int , int> &inv){
    if(breaking){
        if((target_block_x!=x)||(target_block_y!=y)){
            breaking = 0;
            break_block = max_break_block;
            return;
        }
        if(!break_block){
            ear.inventory[get_block(x , y)]++;
            set_block(x , y , 0);
            breaking = 0;
            break_block = max_break_block;
            return;
        }
        break_block --;
    }
    else {
        if(!get_block(x,y))return;
        target_block_x = x;
        target_block_y = y;
        breaking = 1;
        return;
    }
}

void break_block_left(){
    int temp = get_block(cx-1, cy);
    if(!temp)return;
    ear.inventory[temp]++;
    delay(10);
    set_block(cx-1 , cy , 0);
}

void break_block_right(){
    int block = get_block(cx +1 , cy);
    if(!block)return;
    ear.inventory[block]++;
    set_block(cx+1 , cy , 0);
}

void break_block_up(){
    int block = get_block(cx , cy-1);
    if(!block)return;
    ear.inventory[block]++;
    set_block(cx , cy-1 , 0);
}
void break_block_down(){
    int block = get_block(cx , cy+1);
    if(!block)return;
    ear.inventory[block]++;
    set_block(cx , cy+1 , 0);
}

void place_block_up(int i){
    if(get_block(cx , cy-1))return;
    delay(10);
    set_block(cx , cy-1 , i);
    ear.inventory[i]--;
}
void place_block_down(int i){
    if(get_block(cx , cy+1))return;
    delay(10);
    set_block(cx , cy+1 , i);
    ear.inventory[i]--;
}
void place_block_left(int i){
    if(get_block(cx-1 , cy))return;
    delay(10);
    set_block(cx -1 , cy, i);
    ear.inventory[i]--;
}
void place_block_right(int i){
    if(get_block(cx+1 , cy))return;
    delay(10);
    set_block(cx +1 , cy , i);
    ear.inventory[i]--;
}

void reset_physics(){
    jump_hight = 0;
}

void depth_pressure_physics(){
    if(cy<ear.skill["Depth"]*100)return;
    if(tick - depth_damage_tick <= depth_damage_gap)return;
    depth_damage_tick = tick;
    main_hit.push({{0,0} , 1});
}

void death(){
    ear.inventory.clear();
    cy = ear.stl["spawny"];
    cx=0;
    ear.health=max_health;
    win msg;
    msg.name = "msg";
    msg.vs["msg"] = {"You died"};
    wino.push(msg);
}

void physics(){
    if(hit_delay)hit_delay--;
    if((!breaking)&&(break_block!=max_break_block))break_block=max_break_block;
    depth_pressure_physics();
    if(ear.health<=0)death();
}
