#ifndef __Display_h_2018_04_23_14_14
#define __Display_h_2018_04_23_14_14
#include <stdint.h>

#define SCANLINE_LEN 254
#define SCREEN_HEIGHT 240

typedef struct{
    unsigned short data;
}color;

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}rgb;

color fromRGB(rgb);
rgb toRGB(color);
color blend(color,color,float);


typedef struct{
    color colors[256];
}pallate;

typedef struct{
    char pixels[SCANLINE_LEN];
}scanline;

typedef struct{
    scanline lines[SCREEN_HEIGHT];
}screen;

typedef struct{
    int8_t x;
    int8_t y;
    int8_t a;
    int8_t b;
    int8_t c;
    int8_t d;
}mtxParams;

extern pallate* const cgram;
extern screen* const vram;
extern mtxParams* const mode7mtx;
extern const color black;


void computePallate(pallate*,screen*);
void rotateScreen(int);
void moveScreen(int,int);
void strechScreen(float,float);

void nmiRoutine();

#endif
