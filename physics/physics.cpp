
#include "../lib.h"
#include "../stora/stora.h"
#include "../game/chunk.h"
#include "../windows/dynamic/inventory.h"

long long jump_hight = 6;
long long jump_stage = 0;

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
    if(get_mob(vx-1 , vy)!=-1)return;

    if((!get_block(vx-1, vy))||(ghost)){
        vx--;
    }
    else if((!get_block(vx-1 , vy-1))&&(!get_block(vx , vy-1))){
        vx--;
        vy--;
    }
}



void move_right(int &vx , int &vy){

    if(get_mob(vx+1 , vy)!=-1)return;

    if((!get_block(vx+1 , vy))||(ghost)){
        vx++;
    }
    else if((!get_block(vx+1 , vy-1))&&(!get_block(vx , vy-1))){
        vx++;
        vy--;
    }
}

void gravity(int &vx , int &vy){
    if(ghost)return;
    if(jump_stage)return;
    if((!get_block(vx ,vy+1))&&(get_mob(vx , vy+1)==-1)){
        // delay(5);
        vy++;
    }
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

void break_block_left(){
    int temp = get_block(cx-1, cy);
    if(!temp)return;
    ear.inventory[temp]++;
    delay(10);
    set_block(cx-1 , cy , 0);
}

void break_block_right(){
    int temp = get_block(cx+1, cy);
    if(!temp)return;
    ear.inventory[temp]++;
    delay(10);
    set_block(cx+1 , cy , 0);
}
void break_block_up(){
    int temp = get_block(cx, cy-1);
    if(!temp)return;
    ear.inventory[temp]++;
    delay(10);
    set_block(cx , cy-1 , 0);
}
void break_block_down(){
    int temp = get_block(cx, cy+1);
    if(!temp)return;
    ear.inventory[temp]++;
    delay(10);
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