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
int pixelSize = 4;
int attributeSize = pixelSize * 8;

bool initSDL();
void exitSDL();

SDL_Window *mainWindow = nullptr;
SDL_Texture *bitmapTexture = nullptr;
SDL_Renderer *mainRender = nullptr;

Uint64 startTick;
Uint64 endTick;

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

rgb colorPalette0[] = {
        rgb{0, 0, 0}, //BLACK0
        rgb{0, 0, 215}, //BLUE0
        rgb{215, 0, 0}, //RED0
        rgb{215, 0, 215}, //MAGENTA0
        rgb{0, 215, 0}, //GREEN0
        rgb{0, 215, 215}, //CYAN0
        rgb{215, 215, 0}, //YELLOW0
        rgb{215, 215, 215} //WHITE0
};

rgb colorPalette1[] = {
        rgb{0, 0, 0}, //BLACK
        rgb{0, 0, 255}, //BLUE1
        rgb{255, 0, 0}, //RED1
        rgb{255, 0, 255}, //MAGENTA1
        rgb{0, 255, 0}, //GREEN1
        rgb{0, 255, 255}, //CYAN1
        rgb{255, 255, 0}, //YELLOW1
        rgb{255, 255, 255} //WHITE1
};

//bool pixels[191][255] = {false};
std::vector<std::vector<bool>> pixels;

//bool attributes[23][31] = {false};
std::vector<std::vector<bool>> attributes;

#endif //SDL2TEST_MAIN_H
