//
// Created by VokamisAir on 11/29/20.
//

#ifndef SDL2TEST_MAIN_H
#define SDL2TEST_MAIN_H

#include "common.h"
#include "StarFish.h"

//using json = nlohmann::json;

int maxScreenWidth = 1000;
int maxScreenHeight = 760;

bool showGrid = true;
static int pixelSize = 4;
static int attributeSize = pixelSize * 8;

bool initSDL();
void exitSDL();

SDL_Window *mainWindow = nullptr;
SDL_Texture *bitmapTexture = nullptr;
SDL_Renderer *mainRender = nullptr;

Uint64 initialTick;
Uint64 startTick;
Uint64 endTick;
int frameCount;
int zoomLevel = 0;

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

rgb colorPalette0[] = {
        rgb{255, 255, 255}, //WHITE
        rgb{0, 0, 215}, //BLUE0
        rgb{215, 0, 0}, //RED0
        rgb{215, 0, 215}, //MAGENTA0
        rgb{0, 215, 0}, //GREEN0
        rgb{0, 215, 215}, //CYAN0
        rgb{215, 215, 0} //YELLOW0
};

rgb colorPalette1[] = {
        rgb{0, 0, 0}, //BLACK
        rgb{0, 0, 255}, //BLUE1
        rgb{255, 0, 0}, //RED1
        rgb{255, 0, 255}, //MAGENTA1
        rgb{0, 255, 0}, //GREEN1
        rgb{0, 255, 255}, //CYAN1
        rgb{255, 255, 0} //YELLOW1
};

// 256x192 (1x1)
uint8_t pixels[191][255];

// 32x24 (8x8)
uint8_t attributes[23][31];

#endif //SDL2TEST_MAIN_H
