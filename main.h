//
// Created by VokamisAir on 11/29/20.
//

#ifndef SDL2TEST_MAIN_H
#define SDL2TEST_MAIN_H

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <random>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <SDL.h>
#include "common.h"
#include "StarFish.h"

//using json = nlohmann::json;

int MAX_SCREEN_WIDTH = 320;
int MAX_SCREEN_HEIGHT = 240;

bool initSDL();
void exitSDL();

SDL_Window *mainWindow = nullptr;
SDL_Texture *bitmapTexture = nullptr;
SDL_Renderer *mainRender = nullptr;

Uint64 firstTick;
Uint64 startTick;
Uint64 lastTick;
int frameCount;


#endif //SDL2TEST_MAIN_H
