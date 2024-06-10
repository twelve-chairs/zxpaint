//
// Created by VokamisAir on 1/8/21.
//

#ifndef ZXPAINT_STARFISH_H
#define ZXPAINT_STARFISH_H

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


#endif //ZXPAINT_STARFISH_H
