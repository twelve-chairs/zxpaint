//
// Created by VokamisAir on 1/8/21.
//

#include "StarFish.h"

StarFish::StarFish() {
  this->x1 = 0;
  this->x2 = 0;
  this->y1 = 0;
  this->y2 = 0;
  this->width = 0;
  this->height = 0;
  this->lastUpdate = SDL_GetPerformanceCounter();
}


void StarFish::animation(SDL_Renderer* parentRenderer, int new_x1, int new_x2, int new_y1, int new_y2){
  this->x1 = new_x1;
  this->y1 = new_y1;
  this->x2 = new_x2;
  this->y2 = new_y2;

  this->width = abs(x2 - x1);
  this->height = abs(y2 - y1);

  // Technicolor star fish
  for (int n = 0; n < 200; n++) {
    int star_x1 = x1 + (width / 2);
    int star_y1 = y1 + (height / 2);
    int star_x2 = randomInteger(x2, x1);
    int star_y2 = randomInteger(y2, y1);

    SDL_SetRenderDrawColor(parentRenderer, randomInteger(255), randomInteger(255), randomInteger(255),
                           255);
    SDL_RenderDrawLine(parentRenderer, star_x1, star_y1, star_x2, star_y2);
  }
}

StarFish::~StarFish() = default;
