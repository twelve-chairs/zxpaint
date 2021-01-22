//
// Created by VokamisAir on 11/29/20.
//

#ifndef SDL2TEST_MAIN_H
#define SDL2TEST_MAIN_H

#include "common.h"
#include "StarFish.h"


int maxScreenWidth = 1154;
int maxScreenHeight = 768;

bool showGrid = true;
int pixelSize = 4;
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

struct iconLocation {
    int x1;
    int y1;
    int x2;
    int y2;
    bool hover;
};

std::vector<std::vector<rgb>> colorPalette;
std::vector<iconLocation> iconLocations;

std::vector<std::vector<bool>> pixels;
std::vector<std::vector<attribute>> attributes;

const int blockSize = 36;

const char *imageList[] = {
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_zoom_in_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_zoom_out_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_grid_on_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_grid_off_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_up_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_down_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_left_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_right_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_border_color_black_18dp.bmp",
        "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_format_color_fill_black_18dp.bmp"
};

#endif //SDL2TEST_MAIN_H
