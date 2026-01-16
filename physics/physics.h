#ifndef PHYSICS_H
#define PHYSICS_H

bool isbo();
void delay(long long v);
void move_left();
void move_right();
void gravity();
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

#endif