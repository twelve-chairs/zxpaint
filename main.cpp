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

void rightMenu(){
    SDL_Rect fillRect = {maxScreenWidth - 130, 0, 130, maxScreenHeight};
    SDL_SetRenderDrawColor(mainRender, 215, 215, 215, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(mainRender, &fillRect);
}

void drawGrid(int gridSize){
    try {
        if (showGrid) {
            // Minor ticks
            for (int y = 0; y <= pixels[0].size(); y++) {
                for (int x = 0; x < pixels.size(); x++) {
                    SDL_Rect fillRect = {x * gridSize, y * gridSize, gridSize, gridSize};
                    if (pixels[x][y]) {
                        SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(mainRender, &fillRect);
                    } else {
                        if (gridSize >= 4) {
                            SDL_SetRenderDrawColor(mainRender, 128, 128, 128, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawRect(mainRender, &fillRect);
                        }
                    }
                }
            }
        }

        //Major ticks
        int attributeGridSize = gridSize * 8;

        for (int y = 0; y <= attributes[0].size(); y++) {
            for (int x = 0; x <= attributes.size(); x++) {
                SDL_SetRenderDrawColor(mainRender, 20, 20, 20, SDL_ALPHA_OPAQUE);
                SDL_Rect fillRect = {x * attributeGridSize, y * attributeGridSize, attributeGridSize, attributeGridSize};
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

    for (auto color: colorPalette0) {
        SDL_Rect fillRect = {startingPositionX, (temp_index * blockSize) + startingPositionY, blockSize, blockSize};
        SDL_SetRenderDrawColor(mainRender, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
        temp_index++;
    }

    startingPositionX = maxScreenWidth - (100 - blockSize);
    temp_index = 0;
    for (auto color: colorPalette1) {
        SDL_Rect fillRect = {startingPositionX, (temp_index * blockSize) + startingPositionY, blockSize, blockSize};
        SDL_SetRenderDrawColor(mainRender, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
        temp_index++;
    }
}

void loadIcons(){
    const char *images[5][2] = {
            {
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_border_color_black_18dp.bmp",
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_format_color_fill_black_18dp.bmp"
            },
            {
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_zoom_in_black_18dp.bmp",
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_zoom_out_black_18dp.bmp"
            },
            {
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_grid_on_black_18dp.bmp",
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_grid_off_black_18dp.bmp"
            },
            {
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_up_black_18dp.bmp",
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_down_black_18dp.bmp"
            },
            {
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_left_black_18dp.bmp",
                    "/Users/vokamisair/Documents/dev/zxpaint/images/sharp_keyboard_arrow_right_black_18dp.bmp"
            }
    };


    int index = 0;
    int subindex;
    int startingPositionX;
    int startingPositionY;

    for (const auto &layerIndex: images) {
        startingPositionX = maxScreenWidth - 100;
        startingPositionY = 20 + (sizeof(images)/sizeof(images[0]));
        subindex = 0;
        for (const auto &image: layerIndex) {
            if (subindex != 0){
                startingPositionX = maxScreenWidth - (100 - blockSize);
            }
            SDL_Rect bitmapLayer = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};
            SDL_Surface *bitmapImage = SDL_LoadBMP(image);
            bitmapTexture = SDL_CreateTextureFromSurface(mainRender, bitmapImage);
            SDL_FreeSurface(bitmapImage);
            SDL_RenderCopy(mainRender, bitmapTexture, nullptr, &bitmapLayer);
            subindex++;
        }
        index++;
    }
}

int main(int argc, char* args[]){

    try {
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

//                                bitmapLayer.w = maxScreenWidth;
//                                bitmapLayer.h = maxScreenHeight;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
//                            SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
                            mouseLocation.clicked = true;
                            break;
                        case SDL_MOUSEBUTTONUP:
//                            showGrid = !showGrid;
                            mouseLocation.clicked = false;
//                            pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize] = !pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize];
                            break;
                        case SDL_MOUSEMOTION:
                            SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
                            if (mouseLocation.clicked){
                                pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize] = !pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize];
                            }
//                        case SDL_MOUSEWHEEL:
//                            if (!mouseLocation.clicked) {
//                                if (e.wheel.y > 0) // scroll up
//                                {
//                                    pixelSize < 30 ? pixelSize++ : pixelSize = 30;
//                                } else if (e.wheel.y < 0) // scroll down
//                                {
//                                    pixelSize > 2 ? pixelSize-- : pixelSize = 2;
//                                }
//                                attributeSize = pixelSize * 8;
//                            }
//                            break;
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                // IMPORTANT: clear render
                SDL_SetRenderDrawColor(mainRender, colorPalette1[7].r, colorPalette1[7].g, colorPalette1[7].b, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(mainRender);

                // Set background image
//                SDL_RenderCopy(mainRender, bitmapTexture, nullptr, &bitmapLayer);

                drawGrid(pixelSize);
                rightMenu();
                colorSelector();
                loadIcons();

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