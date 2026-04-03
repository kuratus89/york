
#include "../lib.h"
#include "chunk.h"

long long min_surface = 0;
long long max_surface = 20;
long long min_grass = 19;
long long max_grass = 25;
float surface_step=50.0f;
float cave_step = 15.0f;
float cave_depth = 30.0f;
float cave_fading_range = 10.0f;
float ore_step = 3;
int structure_cell = 200;

long long hasher(long long x , long long seed){
    x+=seed*1000;
    x = (x<<13)^x;
    return (x*(x*x*15731 +789221)+ 1376312589);
}

float vap(long long x){
    return (hasher(x , ear.seed)&0x7fffffff)/float(0x7fffffff);
}

float lerp(float a , float b,  float t){
    return (a+t*(b-a));
}

float noise_1d(long long x){
    long long a = floor(x / surface_step) * surface_step; 
    long long b  = a+surface_step;
    float c = vap(a);
    float d = vap(b);
    float t= (x-a)/surface_step;
    t = t * t * (3 - 2 * t);
    return (lerp(c , d , t));
}
float fbm_1d(long long x){
    float ans=0;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0;
    long long steps=6;
    for(long long i=0 ; i<steps ; i++){
        ans+=noise_1d(x*frequency)*amplitude;
        max_value +=amplitude;
        amplitude*=0.5f;
        frequency*=2.0f;
    }
    return (ans/max_value);
}
float fbm_plains(long long x){
    float base = noise_1d(x);
    float detail = noise_1d(x*2);
    return (((detail*0.2f) + (base*0.8f)));
}

long long height(long long x){
    return (min_surface + fbm_plains(x)*(max_surface - min_surface));
}

long long grass(long long x){
    return (min_grass + (fbm_1d(x)*(max_grass - min_grass)));
}

long long hasher_2d(long long x , long long y ){
    long long h = x * 73856093 + y * 19349663;
    h^=ear.seed;
    h = (h<<13)^h;
    return (h*(h*h*15731+789221)+1376312589);
}
float vap_2d(long long x , long long y){
    return (hasher_2d(x , y) & 0x7fffffff) / float(0x7fffffff);
}

float noise_2d(float x , float y , float step){
    float x0 = floor(x/step)*step;
    float x1 = x0 +step;
    float y0 = floor(y/step)*step;
    float y1 = y0 +step;
    float h00 = vap_2d((long long)x0 ,(long long) y0);
    float h01 = vap_2d((long long)x0 ,(long long) y1);
    float h10 = vap_2d((long long)x1 ,(long long) y0);
    float h11 = vap_2d((long long)x1 ,(long long) y1);
    float tx = (x - x0)/step;
    float ty = (y- y0)/step;
    tx = tx*tx*(3- (tx*2));
    ty = ty*ty*(3 - (ty*2));
    float l = lerp(h00 , h10 , tx);
    float m = lerp(h01 , h11 , tx);
    return lerp(l,m , ty);
}

float cave_fbm(float x, float y){
    float val = 0;
    float amp = 0.1f;
    float freq = 1.0f;
    float maxi = 0;
    long long steps = 4;
    for(long long i=0 ; i<steps ; i++){
        val+=noise_2d(x*freq , y*freq , cave_step)*amp;
        maxi+=amp;
        amp*=0.5f;
        freq*=2.0f;
    }
    return (val/maxi);
}

float ore_fbm(float x , float y){
    float val = 0;
    float amp = 1.0f;
    float freq = 1.0f;
    int steps = 5;
    float maxi=0;
    for(int i=0 ; i<steps ; i++){
        val+= noise_2d(x*freq  , y*freq ,ore_step)*amp;
        maxi+=amp;
        freq*=2.8f;
        amp*= 0.5f;
    }
    return val/maxi;
}

bool is_air(long long x , long long y){
    if(y<cave_depth){
        return 0;
    }
    float edge_fallof=1.0f;
    if(y<(cave_depth+cave_fading_range)){
        edge_fallof = (float)(y-cave_depth)/cave_fading_range;
    }
    float threshold = 0.55f +((1.0f - edge_fallof)*0.2f);
    return (cave_fbm((float)x*0.7f ,(float)y* 3.0f)>threshold);
}

bool has_tree(int x){
    float n = fbm_1d(x*0.08f);
    return (n>0.75f);
}

float ore_noise(int x , int y , float scale){
    return ore_fbm((float)x *scale, (float)y*scale);
}


bool is_iron(int x , int y){
    if(y<100)return 0;
    float n = ore_noise(x  ,y , 0.1f);
    n = pow(n , 2.5f);
    float mask = noise_2d(x*0.02f , y*0.02f , 4.0f);
    float breaker = noise_2d(x*0.25f , y*0.25f , 2.0f);
    breaker = pow(breaker , 2.0f);
    return ((n>0.50f)&&(mask>0.25f)&&(breaker>0.25f));
}

bool is_gold(int x , int y){
    if(y<300)return 0;
    float n = ore_noise(x , y , 0.09f);
    n = pow(n , 3.0f);
    float mask = noise_2d(x*0.02f , y*0.02f , 4.0f);
    float breaker = noise_2d(x*0.15f , y*0.15f , 2.0f);
    breaker = pow(breaker , 2.0f);
    return ((n>0.55f)&&(mask>0.15f)&&(breaker>0.15f));
}

bool is_diamond(int x , int y){
    if(y<500)return 0;
    float n = ore_noise(x , y , 0.12f);
    n = pow(n , 3.5f);
    float mask = noise_2d(x*0.02f , y*0.02f , 4.0f);
    float breaker = noise_2d(x*0.25f , y*0.25f , 2.0f);
    breaker = pow(breaker , 2.0f);
    return((n>0.6f)&&(mask>0.15f)&&(breaker>0.15f));
}


   
bool has_struct(int x , int y){
    long long lx = (x>=0)?(x/structure_cell)*structure_cell :((x - structure_cell+1)/structure_cell)*structure_cell;
    long long ly = (y>=0)?(y/structure_cell)*structure_cell :((y - structure_cell+1)/structure_cell)*structure_cell;
    long long h = hasher_2d(lx , ly);
    float c = (h & 0x7fffffff) / float(0x7fffffff);
    if(c<0.55f)return 0;

    int localx = (h>>8)%structure_cell;
    int localy = (h>>16)%structure_cell;
    if(localx<0)localx+=structure_cell;
    if(localy<0)localy+=structure_cell;

    return (((lx+localx)==x)&&((ly+localy)==y));  

}

