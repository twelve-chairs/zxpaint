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

//using json = nlohmann::json;

int MAX_SCREEN_WIDTH = 320;
int MAX_SCREEN_HEIGHT = 240;

bool initSDL();
void exitSDL();
int randomInteger(int to, int from = 0);

SDL_Window *mainWindow = nullptr;
SDL_Texture *bmpTexture = nullptr;
SDL_Renderer *mainRender = nullptr;
SDL_Surface *bmpImage = nullptr;


#endif //SDL2TEST_MAIN_H
