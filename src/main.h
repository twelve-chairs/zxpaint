//
// Created by VokamisAir on 11/29/20.
//

#ifndef SDL2TEST_MAIN_H
#define SDL2TEST_MAIN_H

#include "common.h"
#include "StarFish.h"


int maxScreenWidth = 1154;
int maxScreenHeight = 768;

static bool showGrid = true;
static int pixelSize = 4;
int attributeSize = pixelSize * 8;

bool initSDL();
void exitSDL();

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRender = nullptr;

Uint64 startTick;
Uint64 endTick;

struct mouseLocation {
    int x;
    int y;
    bool clicked;
} mouseLocation;

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct attribute {
    uint8_t ink;
    uint8_t paper;
    bool bright;
};

struct objectLocation {
    int x1;
    int y1;
    int x2;
    int y2;
    bool hover;
    bool selected;
};

attribute selectedColors;

std::vector<std::vector<rgb>> colorPalette;

std::vector<objectLocation> iconLocations;
std::vector<std::vector<objectLocation>> colorLocations;

std::vector<std::vector<bool>> pixels;
std::vector<std::vector<attribute>> attributes;

std::vector<SDL_Texture*> textures;

const int blockSize = 36;

bool ink = true;
bool paper = false;


const char *imageList[] = {
        "images/sharp_zoom_in_black_18dp.bmp",
        "images/sharp_zoom_out_black_18dp.bmp",
        "images/sharp_grid_on_black_18dp.bmp",
        "images/sharp_grid_off_black_18dp.bmp",
        "images/sharp_keyboard_arrow_up_black_18dp.bmp",
        "images/sharp_keyboard_arrow_down_black_18dp.bmp",
        "images/sharp_keyboard_arrow_left_black_18dp.bmp",
        "images/sharp_keyboard_arrow_right_black_18dp.bmp",
        "images/sharp_border_color_black_18dp.bmp",
        "images/sharp_format_color_fill_black_18dp.bmp"
};

#endif //SDL2TEST_MAIN_H
