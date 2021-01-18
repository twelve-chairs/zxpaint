#include "main.h"

bool initSDL() {
    try {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            spdlog::error(SDL_GetError());
            return false;
        }

        mainWindow = SDL_CreateWindow("ZX-Paint (alpha) - Twelve Chairs Software, LLC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      maxScreenWidth, maxScreenHeight, SDL_WINDOW_RESIZABLE);
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

void rightMenu(){
    SDL_Rect fillRect = {maxScreenWidth - 130, 0, 130, maxScreenHeight};
    SDL_SetRenderDrawColor(mainRender, 215, 215, 215, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(mainRender, &fillRect);
}

void drawGrid(int zoomLevel){
    try {
        SDL_Rect fillRect;
        int attributeGridSize = zoomLevel * 8;

        if (showGrid) {
            // Minor ticks
            for (int y = 0; y <= pixels[0].size(); y++) {
                for (int x = 0; x < pixels.size(); x++) {
                    fillRect = {x * zoomLevel, y * zoomLevel, zoomLevel, zoomLevel};
                    if (pixels[x][y]) {
                        SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(mainRender, &fillRect);
                    } else {
                        if (zoomLevel >= 4) {
                            SDL_SetRenderDrawColor(mainRender, 128, 128, 128, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawRect(mainRender, &fillRect);
                        }
                    }
                }
            }
        }

        //Major ticks
        for (int y = 0; y <= attributes[0].size(); y++) {
            for (int x = 0; x <= attributes.size(); x++) {
                SDL_SetRenderDrawColor(mainRender, 20, 20, 20, SDL_ALPHA_OPAQUE);
                fillRect = {x * attributeGridSize, y * attributeGridSize, attributeGridSize, attributeGridSize};
                SDL_RenderDrawRect(mainRender, &fillRect);
            }
        }
    }
    catch (std::exception &e){
        spdlog::error(e.what());
    }
}

void colorSelector(){
    int allColors = blockSize * (sizeof(colorPalette0)/sizeof(colorPalette0[0]));

    int startingPositionX = maxScreenWidth - 100;
    int startingPositionY = (maxScreenHeight - allColors) - 20;
    int temp_index = 0;

    SDL_Rect fillRect;

    for (auto color: colorPalette0) {
        fillRect = {startingPositionX, (temp_index * blockSize) + startingPositionY, blockSize, blockSize};
        SDL_SetRenderDrawColor(mainRender, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
        temp_index++;
    }

    startingPositionX = maxScreenWidth - (100 - blockSize);
    temp_index = 0;
    for (auto color: colorPalette1) {
        fillRect = {startingPositionX, (temp_index * blockSize) + startingPositionY, blockSize, blockSize};
        SDL_SetRenderDrawColor(mainRender, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
        temp_index++;
    }
}

void loadIcons(){

}

// TODO: this is awful. Please revisit.
void drawIcons(){
    icons.clear();

    SDL_Surface *bitmapImage;
    SDL_Rect bitmapLayer;
    SDL_Texture *texture;

    int index = 0;
    int startingPositionX;
    int startingPositionY;

    for (auto &image: imageList){
        bitmapImage = SDL_LoadBMP(image);
        startingPositionX = maxScreenWidth - 104;
        startingPositionY = 20 + (sizeof(imageList) / sizeof(imageList[0]));
        bitmapLayer = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};
        texture = SDL_CreateTextureFromSurface(mainRender, bitmapImage);
        SDL_FreeSurface(bitmapImage);
        SDL_RenderCopy(mainRender, texture, nullptr, &bitmapLayer);
        SDL_DestroyTexture(texture);
        index++;
    }
}

int main(int argc, char* args[]){

    try {
        loadIcons();
        startTick = SDL_GetPerformanceCounter();
        endTick = startTick;

        // 256x192 (1x1) pixels
        pixels = {255, std::vector<bool>(191,false)};
        // 32x24 (8x8) attributes
        attributes = {31, std::vector<bool>(23,false)};

        bool mainLoopRunning = true;

        if (!initSDL()) {
            spdlog::error(SDL_GetError());
        }
        else {
            SDL_Event e;

            SDL_ShowCursor(1);

            SDL_SetRenderDrawColor(mainRender, colorPalette0[0].r, colorPalette0[0].g, colorPalette0[0].b, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mainRender);

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
                                maxScreenWidth = e.window.data1;
                                maxScreenHeight = e.window.data2;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            mouseLocation.clicked = true;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            mouseLocation.clicked = false;
                            break;
                        case SDL_MOUSEMOTION:
                            SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
                            if (mouseLocation.clicked){
                                pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize] = true;
                            }
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                // IMPORTANT: clear render
                SDL_SetRenderDrawColor(mainRender, colorPalette1[7].r, colorPalette1[7].g, colorPalette1[7].b, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(mainRender);

                drawGrid(pixelSize);
                rightMenu();
                colorSelector();
                drawIcons();

                SDL_RenderPresent(mainRender);

                endTick = SDL_GetPerformanceCounter();
                float elapsedMS = (float)(endTick - startTick) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
//                spdlog::info("Elapsed ms: {}", elapsedMS);
            }
        }

        exitSDL();
        return 0;
    }
    catch (const std::exception &e){
        spdlog::error("General error: {}", e.what());
    }
}