//
// Created by VokamisAir on 1/8/21.
//

#ifndef SDL2TEST_STARFISH_H
#define SDL2TEST_STARFISH_H

#include <SDL.h>
#include "common.h"

class StarFish {
public:
    StarFish();
    virtual ~StarFish();

    int x1;
    int x2;
    int y1;
    int y2;
    int lastUpdate;
    int width;
    int height;

    void animation(SDL_Renderer *parentRenderer, int, int, int, int);
};


#endif //SDL2TEST_STARFISH_H
