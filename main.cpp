#include "main.h"

bool initSDL() {
    try {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            spdlog::error(SDL_GetError());
            return false;
        }

        mainWindow = SDL_CreateWindow("Twelve Chairs Software", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if (mainWindow == nullptr){
            spdlog::error(SDL_GetError());
            return false;
        }

        mainRender = SDL_CreateRenderer(mainWindow, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (mainRender == nullptr) {
            spdlog::error(SDL_GetError());
            return false;
        }
        return true;
    }
    catch (const std::exception&){
        spdlog::error(SDL_GetError());
        return false;
    }
}

void exitSDL(){
    try {
        SDL_DestroyTexture(bitmapTexture);
        bitmapTexture = nullptr;
        SDL_DestroyRenderer(mainRender);
        mainRender = nullptr;
        SDL_DestroyWindow(mainWindow);
        mainWindow = nullptr;

        SDL_Quit();
    }
    catch (const std::exception&){
        spdlog::error(SDL_GetError());
    }
}


Uint64 checkFrame(Uint64 end){
    return end - startTick;
}

Uint64 checkFrame(Uint64 end, Uint64 start){
    return end - start;
}

int main(int argc, char* args[]){
    try {
        firstTick = SDL_GetPerformanceCounter();
        startTick = SDL_GetPerformanceCounter();
        lastTick = startTick;
        frameCount = 1;

        bool mainLoopRunning = true;

        if (!initSDL()) {
            spdlog::error(SDL_GetError());
        }
        else {
            SDL_Event e;

            SDL_ShowCursor(1);

            SDL_Rect bitmapLayer = {0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT};
            SDL_Surface *bitmapImage = SDL_LoadBMP("/Users/vokamisair/Documents/dev/sdl2/nothing.bmp");
            bitmapTexture = SDL_CreateTextureFromSurface(mainRender, bitmapImage);
            SDL_FreeSurface(bitmapImage);
            SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 255);
            SDL_RenderClear(mainRender);

            StarFish newStar;

            while (mainLoopRunning) {
                startTick = SDL_GetPerformanceCounter();
                // Get events for main loop
                while (SDL_PollEvent(&e) != 0) {
                    switch (e.type){
                        case SDL_QUIT:
                            spdlog::info("SDL exiting");
                            mainLoopRunning = false;
                            break;
                        case SDL_WINDOWEVENT:
                            if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                                MAX_SCREEN_WIDTH = e.window.data1;
                                MAX_SCREEN_HEIGHT = e.window.data2;


                                bitmapLayer.w = MAX_SCREEN_WIDTH;
                                bitmapLayer.h = MAX_SCREEN_HEIGHT;
                            }
                            break;
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                // IMPORTANT: clear render
                SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 0);
                SDL_RenderClear(mainRender);

                // Set background image
                SDL_RenderCopy(mainRender, bitmapTexture, nullptr, &bitmapLayer);

                newStar.width = 100;
                newStar.height = 100;

                //Top-left
                newStar.animation(mainRender, 0, newStar.width, 0, newStar.height);
                //Top-right
                newStar.animation(mainRender, MAX_SCREEN_WIDTH-newStar.width, (MAX_SCREEN_WIDTH-newStar.width) + newStar.width, 0, newStar.height);
                //Bottom-left
                newStar.animation(mainRender, 0, newStar.width, MAX_SCREEN_HEIGHT-newStar.height, MAX_SCREEN_HEIGHT);
                //Bottom-right
                newStar.animation(mainRender, MAX_SCREEN_WIDTH-newStar.width, MAX_SCREEN_WIDTH,  MAX_SCREEN_HEIGHT-newStar.height, MAX_SCREEN_HEIGHT);

                SDL_RenderPresent(mainRender);

                lastTick = SDL_GetPerformanceCounter();
                float elapsedMS = (float)(lastTick - startTick) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
                spdlog::info(elapsedMS);
            }
        }

        exitSDL();
        return 0;
    }
    catch (const std::exception &e){
        spdlog::error("General error: {}", e.what());
    }
}