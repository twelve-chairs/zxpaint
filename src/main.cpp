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
    SDL_SetRenderDrawColor(mainRender, 215, 215, 215, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(mainRender, &fillRect);
}

void drawGrid(int zoomLevel){
    try {
        SDL_Rect fillRect;
        int attributeGridSize = zoomLevel * 8;

        for (int y = 0; y < attributes[0].size(); y++) {
            for (int x = 0; x < attributes.size(); x++) {
                fillRect = {x * attributeGridSize, y * attributeGridSize, attributeGridSize, attributeGridSize};
                attribute attr = attributes.at(x).at(y);
                SDL_SetRenderDrawColor(mainRender, colorPalette[attr.bright][attr.paper].r,
                                       colorPalette[attr.bright][attr.paper].g,
                                       colorPalette[attr.bright][attr.paper].b, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(mainRender, &fillRect);

                int start_y = y * 8;
                int start_x = x * 8;
                for (int pixel_y = start_y; pixel_y <= start_y + 8; pixel_y++) {
                    for (int pixel_x = start_x; pixel_x < start_x + 8; pixel_x++) {
                        fillRect = {pixel_x * zoomLevel, pixel_y * zoomLevel, zoomLevel, zoomLevel};
                        if (pixels[pixel_x][pixel_y]) {
                            SDL_SetRenderDrawColor(mainRender, colorPalette[attr.bright][attr.ink].r,
                                                   colorPalette[attr.bright][attr.ink].g,
                                                   colorPalette[attr.bright][attr.ink].b, SDL_ALPHA_OPAQUE);
                            SDL_RenderFillRect(mainRender, &fillRect);
                        }
                    }
                }

                SDL_SetRenderDrawColor(mainRender, 20, 20, 20, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(mainRender, &fillRect);
            }
        }
        if (showGrid) {
            // Minor ticks
            for (int y = 0; y <= pixels[0].size(); y++) {
                for (int x = 0; x < pixels.size(); x++) {
                    fillRect = {x * zoomLevel, y * zoomLevel, zoomLevel, zoomLevel};
                    if (zoomLevel >= 4) {
                        SDL_SetRenderDrawBlendMode(mainRender, SDL_BLENDMODE_BLEND);
                        SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 50);
                        SDL_RenderDrawRect(mainRender, &fillRect);
                    }
                }
            }
        }
    }
    catch (std::exception &e){
        spdlog::error(e.what());
    }
}

void colorSelector(){
    int allColors = blockSize * colorPalette[0].size();
    int startingPositionX = maxScreenWidth - 100;
    int startingPositionY = (maxScreenHeight - allColors) - 20;
    SDL_Rect fillRect;

    for (int index = 0; index <= 1; index++) {
        int subindex = 0;
        for (auto color: colorPalette[index]) {
            fillRect = {(startingPositionX + index) + (index * blockSize), startingPositionY + (subindex * blockSize), blockSize, blockSize};
            SDL_SetRenderDrawColor(mainRender, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(mainRender, &fillRect);
            fillRect = {(startingPositionX + index) + (index * blockSize), startingPositionY + (subindex * blockSize), blockSize, blockSize};
            SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(mainRender, &fillRect);
            subindex++;
        }
    }
}

// TODO: this is awful. Please revisit.
void drawIcons(){
    SDL_Surface *bitmapImage;
    SDL_Rect bitmapLayer;
    SDL_Texture *texture;
    SDL_Rect outlineRect;

    int index = 0;
    int startingPositionX;
    int startingPositionY;

    for (auto &image: imageList){
        bitmapImage = SDL_LoadBMP(image);
        startingPositionX = maxScreenWidth - 100;
        startingPositionY = 20 + (sizeof(imageList) / sizeof(imageList[0]));
        if (index % 2 == 0){
            bitmapLayer = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};
            outlineRect = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};

            iconLocations[index].x1 = startingPositionX;
            iconLocations[index].x2 = startingPositionX + blockSize;
        }
        else {
            startingPositionY -= blockSize;
            bitmapLayer = {startingPositionX + blockSize + 1, (index * blockSize) + startingPositionY, blockSize, blockSize};
            outlineRect = {startingPositionX + blockSize + 1, (index * blockSize) + startingPositionY, blockSize, blockSize};

            iconLocations[index].x1 = startingPositionX + blockSize + 1;
            iconLocations[index].x2 = (startingPositionX + blockSize + 1) + blockSize;
        }
        iconLocations[index].y1 = (index * blockSize) + startingPositionY;
        iconLocations[index].y2 = ((index * blockSize) + startingPositionY) + blockSize;

        texture = SDL_CreateTextureFromSurface(mainRender, bitmapImage);
        SDL_FreeSurface(bitmapImage);

        SDL_SetRenderDrawColor(mainRender, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &outlineRect);

        SDL_RenderCopy(mainRender, texture, nullptr, &bitmapLayer);
        SDL_DestroyTexture(texture);

        for (auto _: iconLocations){
            if ((iconLocations[index].x1 <= mouseLocation.x && mouseLocation.x <= iconLocations[index].x2) &&
                (iconLocations[index].y1 <= mouseLocation.y && mouseLocation.y <= iconLocations[index].y2)){
                iconLocations[index].hover = true;

                SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(mainRender, &outlineRect);
                if (index == 0 && mouseLocation.clicked) {
                    if (pixelSize <= 200){
                        pixelSize += 1;
                    }
                }
                if (index == 1 && mouseLocation.clicked) {
                    if (pixelSize >= 2) {
                        pixelSize -= 1;
                    }
                }
                if (index == 2 && mouseLocation.clicked) {
                    showGrid = true;
                }
                if (index == 3 && mouseLocation.clicked) {
                    showGrid = false;
                }
            }
            else {
                iconLocations[index].hover = false;
            }
        }

        index++;
    }
}

int main(int argc, char* args[]){
    try {
        startTick = SDL_GetPerformanceCounter();
        endTick = startTick;

        // 256x192 (1x1) pixels
        pixels = {256, std::vector<bool>(192,false)};
        // 32x24 (8x8) attributes
        attributes = {32, std::vector<attribute>(24, {0, 7, 0})};

        colorPalette = {
                {
                        rgb{0, 0, 0}, //BLACK0
                        rgb{0, 0, 215}, //BLUE0
                        rgb{215, 0, 0}, //RED0
                        rgb{215, 0, 215}, //MAGENTA0
                        rgb{0, 215, 0}, //GREEN0
                        rgb{0, 215, 215}, //CYAN0
                        rgb{215, 215, 0}, //YELLOW0
                        rgb{215, 215, 215} //WHITE0
                },
                {
                        rgb{0, 0, 0}, //BLACK1
                        rgb{0, 0, 255}, //BLUE1
                        rgb{255, 0, 0}, //RED1
                        rgb{255, 0, 255}, //MAGENTA1
                        rgb{0, 255, 0}, //GREEN1
                        rgb{0, 255, 255}, //CYAN1
                        rgb{255, 255, 0}, //YELLOW1
                        rgb{255, 255, 255} //WHITE1
                }
        };

        for (auto &image: imageList) {
            iconLocation location = {
                    location.x1 = 0,
                    location.y1 = 0,
                    location.x2 = 0,
                    location.y2 = 0,
                    location.hover = false
            };
            iconLocations.push_back(location);
        }

        bool mainLoopRunning = true;

        if (!initSDL()) {
            spdlog::error(SDL_GetError());
        }
        else {
            SDL_Event e;

            SDL_ShowCursor(1);

            SDL_SetRenderDrawColor(mainRender, colorPalette[0][0].r, colorPalette[0][0].g, colorPalette[0][0].b, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mainRender);

            while (mainLoopRunning) {
                startTick = SDL_GetPerformanceCounter();
                int index = 0;
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
                                attributes[(mouseLocation.x / pixelSize) / 8][(mouseLocation.y / pixelSize) / 8].paper = 2;
                            }
                            break;
                        case SDL_KEYDOWN:
                            break;
                    }
                }

                // IMPORTANT: clear render
                SDL_SetRenderDrawColor(mainRender, colorPalette[1][7].r, colorPalette[1][7].g, colorPalette[1][7].b, SDL_ALPHA_OPAQUE);
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