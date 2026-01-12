
#include "../lib.h"

long long seed = 234543245;
long long min_surface = 0;
long long max_surface = 20;

long long hasher(long long x , long long seed){
    x+=seed*1000;
    x = (x<<13)^x;
    return (x*(x*x*15731 +789221)+ 1376312589);
}

float value_at_point(long long x){
    return (hasher(x , seed)&0x7fffffff)/float(0x7fffffff);
}

float lerp(float a , float b,  float t){
    return (a+t*(b-a));
}

float noise_1d(long long x){
    long long a = floor(x / 10.0f) * 10; 
    long long b  = a+10;
    float c = value_at_point(a);
    float d = value_at_point(b);
    float t = (x-a)/10.0f;
    return (lerp(c , d , t));
}

long long height(long long x){
    return (min_surface + noise_1d(x)*(max_surface - min_surface));
}
