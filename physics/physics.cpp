
#include "../lib.h"
#include "../stora/stora.h"
#include "../game/chunk.h"

long long jump_hight = 8;
long long jump_stage = 0;

bool isbo(){
    return(cy==y-6);
}

void delay(long long v){
    this_thread::sleep_for(std::chrono::milliseconds(v));
}

void move_left(){
    if(!get_block(cx-1, cy)){
        cx--;
    }
    else if(!get_block(cx-1 , cy-1)){
        cx--;
        cy--;
    }
}

bool is_ground(){
    return(get_block(cx , cy+1));
}

void move_right(){
    if(!get_block(cx+1 , cy)){
        cx++;
    }
    else if(!get_block(cx+1 , cy-1)){
        cx++;
        cy--;
    }
}

void gravity(){
    if(jump_stage)return;
    if(!get_block(cx ,cy+1)){
        cy++;
    }
}
void jump(){
    if(jump_stage)return;
    if(!is_ground())return;
    if(!get_block(cx , cy-1)){
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
            // delay(20);
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