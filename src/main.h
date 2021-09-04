//
// Created by VokamisAir on 11/29/20.
//

#ifndef ZXPAINT_MAIN_H
#define ZXPAINT_MAIN_H

#include "common.h"

// BEGIN: Include all images
#include "../res/iconsin.xpm"
#include "../res/iconsout.xpm"
#include "../res/iconson.xpm"
#include "../res/iconsoff.xpm"
#include "../res/iconsup.xpm"
#include "../res/iconsdown.xpm"
#include "../res/iconsleft.xpm"
#include "../res/iconsright.xpm"
#include "../res/iconsink.xpm"
#include "../res/iconspaper.xpm"
#include "StarFish.h"

const auto icons = {
        &iconsin,
        &iconsout,
        &iconson,
        &iconsoff,
        &iconsup,
        &iconsdown,
        &iconsleft,
        &iconsright,
        &iconsink,
        &iconspaper
};
// END: Include all images


int maxScreenWidth = 1154;
int maxScreenHeight = 768;

static bool showGrid = true;
static int pixelSize = 4;
int attributeSize = pixelSize * 8;

const int blockSize = 36;

bool ink;
bool paper;

bool initSDL();
void exitSDL();

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRender = nullptr;
SDL_Rect mainGrid;
SDL_Rect mainMenu;

const int MENUWIDTH = 130;

Uint64 startTick;
Uint64 endTick;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct {
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

struct colorLocation {
    int n = -1;
    int m = -1;
};

attribute selectedColors;

std::vector<std::vector<rgb>> colorPalette;

std::vector<objectLocation> iconLocations;
std::vector<std::vector<objectLocation>> colorLocations;

std::vector<std::vector<bool>> pixels;
std::vector<std::vector<attribute>> attributes;

std::vector<SDL_Texture*> textures;


#endif //ZXPAINT_MAIN_H
