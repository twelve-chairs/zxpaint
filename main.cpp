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

void rightMenu(SDL_Renderer* parentRenderer){
    SDL_Rect fillRect = {maxScreenWidth - 160, 0, 160, maxScreenHeight};
    SDL_SetRenderDrawColor(parentRenderer, 215, 215, 215, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(parentRenderer, &fillRect);
}

void colorSelector(SDL_Renderer* parentRenderer){
    int colorWidth = 50;
    int colorHeight = 50;
    int allColors = (colorHeight * 8);

    int startingPositionX = maxScreenWidth - 130;
    int startingPositionY = (maxScreenHeight - allColors) - 20;
    int temp_index = 0;

    for (auto color: colorPalette0) {
        SDL_Rect fillRect = {startingPositionX, (temp_index * colorHeight) + startingPositionY, colorWidth, colorHeight};
        SDL_SetRenderDrawColor(parentRenderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(parentRenderer, &fillRect);
        temp_index++;
    }

    startingPositionX = maxScreenWidth - (130 - colorWidth);
    temp_index = 0;
    for (auto color: colorPalette1) {
        SDL_Rect fillRect = {startingPositionX, (temp_index * colorHeight) + startingPositionY, colorWidth, colorHeight};
        SDL_SetRenderDrawColor(parentRenderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(parentRenderer, &fillRect);
        temp_index++;
    }
}

void drawGrid(SDL_Renderer* parentRenderer, int gridSize){
    try {
        if (showGrid) {
            // Minor ticks
            for (int y = 0; y <= pixels[0].size(); y++) {
                for (int x = 0; x < pixels.size(); x++) {
                    SDL_Rect fillRect = {x * gridSize, y * gridSize, gridSize, gridSize};
                    if (pixels[x][y]) {
                        SDL_SetRenderDrawColor(parentRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(parentRenderer, &fillRect);
                    } else {
                        SDL_SetRenderDrawColor(parentRenderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
                        SDL_RenderDrawRect(parentRenderer, &fillRect);
                    }
                }
            }

            //Major ticks
            int attributeGridSize = gridSize * 8;

            for (int y = 0; y <= attributes[0].size(); y++) {
                for (int x = 0; x <= attributes.size(); x++) {
                    SDL_SetRenderDrawColor(parentRenderer, 20, 20, 20, SDL_ALPHA_OPAQUE);
                    SDL_Rect fillRect = {x * attributeGridSize, y * attributeGridSize, attributeGridSize, attributeGridSize};
                    SDL_RenderDrawRect(parentRenderer, &fillRect);
                }
            }
        }
    }
    catch (std::exception &e){
        spdlog::error(e.what());
    }
}

int main(int argc, char* args[]){

    try {
        startTick = SDL_GetPerformanceCounter();
        endTick = startTick;

        // 256x192 (1x1)
        pixels = {255, std::vector<bool>(191,false)};

        // 32x24 (8x8)
        attributes = {31, std::vector<bool>(23,false)};

        bool mainLoopRunning = true;


//        int attr_rows = (sizeof attributes / sizeof attributes[0]);
//        int attr_columns = sizeof attributes[0] / sizeof(bool);
//        for (int x = 0; x < attr_columns; x++) {
//            for (int y = 0; y < attr_rows; y++) {
//                attributes[x][y] = false;
//            }
//        }
//
//        int pixel_rows = (sizeof pixels / sizeof pixels[0]);
//        int pixel_columns = sizeof pixels[0] / sizeof(bool);
//        for (int x = 0; x < pixel_columns; x++) {
//            for (int y = 0; y < pixel_rows; y++) {
//                pixels[x][y] = false;
//            }
//        }

        if (!initSDL()) {
            spdlog::error(SDL_GetError());
        }
        else {
            SDL_Event e;

            SDL_ShowCursor(1);

            SDL_Rect bitmapLayer = {0, 0, maxScreenWidth, maxScreenHeight};
            SDL_Surface *bitmapImage = SDL_LoadBMP("/Users/vokamisair/Documents/dev/sdl2/nothing.bmp");
            bitmapTexture = SDL_CreateTextureFromSurface(mainRender, bitmapImage);
            SDL_FreeSurface(bitmapImage);
            SDL_SetRenderDrawColor(mainRender, colorPalette0[0].r, colorPalette0[0].g, colorPalette0[0].b, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mainRender);

//            memset(pixels, false, sizeof pixels);

//            for (auto each: pixels){
//                spdlog::info("0: {}", each);
//                spdlog::info("1: {}", each[1]);
//                spdlog::info("1: {}", each[2]);
//            }

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

                                bitmapLayer.w = maxScreenWidth;
                                bitmapLayer.h = maxScreenHeight;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
//                            showGrid = !showGrid;
                            int x, y;
                            SDL_GetMouseState( &x, &y );
//                            try {
                            x = x / pixelSize;
                            y = y / pixelSize;
                            pixels[x][y] = !pixels[x][y];
                            spdlog::info("{} x {} = {}", x, y, pixels[x][y]);
//                            }
//                            catch (std::exception &e) {
//                                spdlog::error(e);
//                            }
                            break;
                        case SDL_MOUSEWHEEL:
                            if(e.wheel.y > 0) // scroll up
                            {
                                pixelSize < 30 ? pixelSize++ : pixelSize = 30;
                            }
                            else if(e.wheel.y < 0) // scroll down
                            {
                                pixelSize > 3 ? pixelSize-- : pixelSize = 3;
                            }
                            attributeSize = pixelSize * 8;
                            break;
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                // IMPORTANT: clear render
                SDL_SetRenderDrawColor(mainRender, colorPalette1[7].r, colorPalette1[7].g, colorPalette1[7].b, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(mainRender);

                // Set background image
//                SDL_RenderCopy(mainRender, bitmapTexture, nullptr, &bitmapLayer);

                drawGrid(mainRender, pixelSize);
                rightMenu(mainRender);
                colorSelector(mainRender);

//                newStar.width = 8;
//                newStar.height = 8;

                //Top-left
//                newStar.animation(mainRender, 0, newStar.width, 0, newStar.height);
                //Top-right
//                newStar.animation(mainRender, maxScreenWidth - newStar.width, maxScreenWidth, 0, newStar.height);
                //Bottom-left
//                newStar.animation(mainRender, 0, newStar.width, maxScreenHeight - newStar.height, maxScreenHeight);
                //Bottom-right
//                newStar.animation(mainRender, maxScreenWidth - newStar.width, maxScreenWidth, maxScreenHeight - newStar.height, maxScreenHeight);

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