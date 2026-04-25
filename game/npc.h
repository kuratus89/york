#ifndef NPC_H
#define NPC_H
#include "../stora/stora.h"

void mob_manager( mob &mo);
void spawn(int x , int y , int type , chunks *ck);
void spawn_this_mob(mob &mo);
void manage_hit();
bool rand_spawn(int x , int y , int type , chunks *ck );
extern long long main_hit_delay;
extern queue<pair<pair<long long ,long long>,long long>> main_hit;

#endif