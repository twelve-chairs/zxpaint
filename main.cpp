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

        mainRender = SDL_CreateRenderer(mainWindow, -1, 0);
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
        SDL_DestroyTexture(mainTexture);
        mainTexture = nullptr;
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

int randomInteger(int to, int from){
    std::random_device randomizerSeed;
    std::default_random_engine randomEngine(randomizerSeed());
    std::uniform_int_distribution<int> randomRange(from, to);
    return randomRange(randomEngine);
}

int main(int argc, char* args[]){
    try {
        if (!initSDL()) {
            spdlog::error(SDL_GetError());
        }
        else {
            bool mainLoopRunning = true;

            SDL_Event e;

            SDL_ShowCursor(1);

            SDL_Rect destinationRect;
            destinationRect.h = 20;
            destinationRect.w = 20;

            bmpImage = SDL_LoadBMP("/Users/vokamisair/Documents/dev/sdl2/nothing.bmp");
            mainTexture = SDL_CreateTextureFromSurface(mainRender, bmpImage);
            SDL_FreeSurface(bmpImage);

            while (mainLoopRunning) {
                // Get events for main loop
                while (SDL_PollEvent(&e) != 0) {
                    switch (e.type){
                        case SDL_QUIT:
                            spdlog::info("SDL exiting");
                            mainLoopRunning = false;
                            break;
                        case SDL_WINDOWEVENT:
                            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                                MAX_SCREEN_WIDTH = e.window.data1;
                                MAX_SCREEN_HEIGHT = e.window.data2;
                            }
                            break;
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                destinationRect.x = randomInteger(MAX_SCREEN_WIDTH);
                destinationRect.y = randomInteger(MAX_SCREEN_HEIGHT);

                // Clear screen with color
                SDL_SetRenderDrawColor(mainRender, 255, 255, 255, 255);
                SDL_RenderClear(mainRender);

                // Set line color
                SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 255);

                int temp_x = randomInteger(MAX_SCREEN_WIDTH);
                int temp_y = randomInteger(MAX_SCREEN_HEIGHT);

                SDL_RenderDrawLine(mainRender, destinationRect.x, destinationRect.y, temp_x, temp_y);
                SDL_RenderCopy(mainRender, mainTexture, nullptr, &destinationRect);
                SDL_RenderPresent(mainRender);
                SDL_Delay(50);
            }
        }

        exitSDL();
        return 0;
    }
    catch (const std::exception &e){
        spdlog::error("General error: {}", e.what());
    }
}