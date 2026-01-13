
#include "../lib.h"

long long seed = 234543245;
long long min_surface = 0;
long long max_surface = 20;
long long min_grass = 19;
long long max_grass = 25;
float surface_step=50.0f;
float cave_step = 15.0f;
float cave_depth = 30.0f;
float cave_fading_range = 10.0f;

long long hasher(long long x , long long seed){
    x+=seed*1000;
    x = (x<<13)^x;
    return (x*(x*x*15731 +789221)+ 1376312589);
}

float vap(long long x){
    return (hasher(x , seed)&0x7fffffff)/float(0x7fffffff);
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
    long long steps=4;
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
    long long h = x *374761393 + y * 668265263;
    h^=seed;
    h = (h<<13)^h;
    return (h*(h*h*15731+789221)+1376312589);
}
float vap_2d(long long x , long long y){
    return (hasher_2d(x , y) & 0x7fffffff) / float(0x7fffffff);
}

float noise_2d(float x , float y){
    float x0 = floor(x/cave_step)*cave_step;
    float x1 = x0 +cave_step;
    float y0 = floor(y/cave_step)*cave_step;
    float y1 = y0 +cave_step;
    float h00 = vap_2d((long long)x0 ,(long long) y0);
    float h01 = vap_2d((long long)x0 ,(long long) y1);
    float h10 = vap_2d((long long)x1 ,(long long) y0);
    float h11 = vap_2d((long long)x1 ,(long long) y1);
    float tx = (x - x0)/cave_step;
    float ty = (y- y0)/cave_step;
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
    long long steps = 3;
    for(long long i=0 ; i<steps ; i++){
        val+=noise_2d(x*freq , y*freq)*amp;
        maxi+=amp;
        amp*=0.5f;
        freq*=2.0f;
    }
    return (val/maxi);
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
