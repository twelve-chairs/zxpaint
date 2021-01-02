//
// Created by VokamisAir on 11/29/20.
//

#ifndef SDL2TEST_MAIN_H
#define SDL2TEST_MAIN_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const int MAX_SCREEN_WIDTH = 320;
const int MAX_SCREEN_HEIGHT = 240;

bool initSDL();
bool loadBMP();
void exitSDL();

SDL_Window* mainWindow = nullptr;
SDL_Surface* mainSurface = nullptr;
SDL_Surface* bmpImage = nullptr;

#endif //SDL2TEST_MAIN_H
