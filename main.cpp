//Using SDL and standard IO
#include "main.h"

bool initSDL() {
    try {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << SDL_GetError() << std::endl;
            return false;
        }

        mainWindow = SDL_CreateWindow("Twelve Chairs Software", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mainWindow == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            return false;
        } else {
            try {
                mainSurface = SDL_GetWindowSurface(mainWindow);
                return true;
            }
            catch (const std::exception &) {
                std::cout << SDL_GetError() << std::endl;
                return false;
            }
        }
    }
    catch (const std::exception&){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
}

bool loadBMP() {
    try {
        bmpImage = SDL_LoadBMP("/Users/vokamisair/Documents/dev/sdl2/nothing.bmp");
        if (bmpImage == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }
    catch (const std::exception&){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
}

void exitSDL(){
    try {
        SDL_FreeSurface(bmpImage);
        bmpImage = nullptr;

        SDL_DestroyWindow(mainWindow);
        mainWindow = nullptr;

        SDL_Quit();
    }
    catch (const std::exception&){}
}

int main(int argc, char* args[]){
    try {
        if (!initSDL()) {
            std::cout << "Failed to initialize SDL!" << std::endl;
        } else {
            if (!loadBMP()) {
                std::cout << "Failed to load media!" << std::endl;
            } else {
                bool mainLoopRunning = true;

                SDL_Event e;

                SDL_ShowCursor(0);

                SDL_Rect destinationRect;
                std::default_random_engine randomEngine;
                std::uniform_int_distribution<int> randomRange(0, MAX_SCREEN_WIDTH);

                while (mainLoopRunning) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            mainLoopRunning = false;
                        }
                    }

                    destinationRect.x = randomRange(randomEngine);
                    destinationRect.y = randomRange(randomEngine);

                    SDL_BlitSurface(bmpImage, nullptr, mainSurface, &destinationRect);

                    SDL_UpdateWindowSurface(mainWindow);

                }
            }
        }

        exitSDL();
        return 0;
    }
    catch (const std::exception&){
        std::cout << "General error" << std::endl;
    }
}