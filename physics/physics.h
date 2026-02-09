#ifndef PHYSICS_H
#define PHYSICS_H

bool isbo();
void delay(long long v);
void move_left(int &vx , int &vy);
void move_right(int &vx , int &vy);
void gravity(int &vx , int &vy);
void manage_jump();
void jump();
void break_block_left();
void break_block_right();
void break_block_up();
void break_block_down();
void place_block_up(int i);
void place_block_down(int i);
void place_block_right(int i);
void place_block_left(int i);
void reset_physics();
void hit();
void physics();

#endif