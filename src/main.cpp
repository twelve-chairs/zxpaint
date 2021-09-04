#include "main.h"

bool initSDL() {
    try {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            spdlog::error(SDL_GetError());
            return false;
        }

        mainWindow = SDL_CreateWindow("ZX-Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      maxScreenWidth, maxScreenHeight, SDL_WINDOW_RESIZABLE);
        if (mainWindow == nullptr){
            spdlog::error(SDL_GetError());
            return false;
        }

        mainRender = SDL_CreateRenderer(mainWindow, 0,  SDL_RENDERER_ACCELERATED);
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

void drawRightMenuPane(){
    try {
        SDL_Rect fillRect = {0, 0, 130, maxScreenHeight};
        SDL_SetRenderDrawColor(mainRender, 220, 220, 220, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void drawScreen(){
    try {
        SDL_Rect fillRect;
        int attributeGridSize = pixelSize * 8;

        for (int y = 0; y < attributes[0].size(); y++) {
            for (int x = 0; x < attributes.size(); x++) {
                fillRect = {x * attributeGridSize, y * attributeGridSize, attributeGridSize, attributeGridSize};
                attribute attr = attributes.at(x).at(y);
                auto temp = colorPalette[attr.bright][attr.paper];
                SDL_SetRenderDrawColor(mainRender, temp.r, temp.g, temp.b, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(mainRender, &fillRect);

                int start_y = y * 8;
                int start_x = x * 8;
                for (int pixel_y = start_y; pixel_y <= start_y + 8; pixel_y++) {
                    for (int pixel_x = start_x; pixel_x < start_x + 8; pixel_x++) {
                        fillRect = {pixel_x * pixelSize, pixel_y * pixelSize, pixelSize, pixelSize};
                        if (pixels[pixel_x][pixel_y]) {
                            temp = colorPalette[attr.bright][attr.ink];
                            SDL_SetRenderDrawColor(mainRender, temp.r, temp.g, temp.b, SDL_ALPHA_OPAQUE);
                            SDL_RenderFillRect(mainRender, &fillRect);
                        }
                    }
                }

                SDL_SetRenderDrawColor(mainRender, 20, 20, 20, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(mainRender, &fillRect);
            }
        }
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void drawGrid(){
    try {
        if (showGrid) {
            SDL_Rect fillRect;
            // Minor ticks
            for (int y = 0; y < pixels[0].size(); y++) {
                for (int x = 0; x < pixels.size(); x++) {
                    fillRect = {x * pixelSize, y * pixelSize, pixelSize, pixelSize};
                    if (pixelSize >= 4) {
                        SDL_SetRenderDrawBlendMode(mainRender, SDL_BLENDMODE_BLEND);
                        SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 15);
                        SDL_RenderDrawRect(mainRender, &fillRect);
                    }
                }
            }
            // Major ticks
            for (int y = 0; y < attributes[0].size(); y++) {
                for (int x = 0; x < attributes.size(); x++) {
                    fillRect = {x * attributeSize, y * attributeSize, attributeSize, attributeSize};
                    if (pixelSize >= 4) {
                        SDL_SetRenderDrawBlendMode(mainRender, SDL_BLENDMODE_BLEND);
                        SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 30);
                        SDL_RenderDrawRect(mainRender, &fillRect);
                    }
                }
            }
        }
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void drawColorOptions(){
    try {
        int allColors = blockSize * colorPalette[0].size();
        int startingPositionX = 30;
        int startingPositionY = (maxScreenHeight - allColors) - 20;
        SDL_Rect fillRect;

        for (int index = 0; index < colorLocations.size(); index++) {
//            int offset = 0;
            for (int subindex = 0; subindex < colorLocations[index].size(); subindex++) {
//                offset = (subindex <= 0) ? 0 : 1;
                fillRect = {
                        (startingPositionX + index) + (index * blockSize),
                        (startingPositionY + (subindex * blockSize)),
                        blockSize,
                        blockSize
                };
                SDL_SetRenderDrawColor(mainRender,
                                       colorPalette[index][subindex].r,
                                       colorPalette[index][subindex].g,
                                       colorPalette[index][subindex].b,
                                       SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(mainRender, &fillRect);

                colorLocations.at(index).at(subindex) = {
                        fillRect.x, fillRect.y, fillRect.x + blockSize, fillRect.y + blockSize
                };
            }
        }

        // Ink color
        fillRect = {
                iconLocations[8].x1 + 1,
                iconLocations[8].y1 + 30,
                blockSize - 2,
                5
        };
        SDL_SetRenderDrawColor(mainRender,
                               colorPalette[selectedColors.bright][selectedColors.ink].r,
                               colorPalette[selectedColors.bright][selectedColors.ink].g,
                               colorPalette[selectedColors.bright][selectedColors.ink].b,
                               SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);

        // Paper color
        fillRect = {
                iconLocations[9].x1 + 1,
                iconLocations[9].y1 + 30,
                blockSize - 2,
                5
        };
        SDL_SetRenderDrawColor(mainRender,
                               colorPalette[selectedColors.bright][selectedColors.paper].r,
                               colorPalette[selectedColors.bright][selectedColors.paper].g,
                               colorPalette[selectedColors.bright][selectedColors.paper].b,
                               SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(mainRender, &fillRect);
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void drawIcons(){
    try {
        SDL_Rect bitmapLayer;
        SDL_Rect outlineRect;

        int index = 0;
        int startingPositionX;
        int startingPositionY;

        for (SDL_Texture* texture: textures) {
            startingPositionX = 30;
            startingPositionY = 20 + (icons.size() / sizeof(icons));
            if (index % 2 == 0) {
                bitmapLayer = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};
                outlineRect = {startingPositionX, (index * blockSize) + startingPositionY, blockSize, blockSize};

                iconLocations[index].x1 = startingPositionX;
                iconLocations[index].x2 = startingPositionX + blockSize;
            } else {
                startingPositionY -= blockSize;
                bitmapLayer = {startingPositionX + blockSize + 1, (index * blockSize) + startingPositionY, blockSize,
                               blockSize};
                outlineRect = {startingPositionX + blockSize + 1, (index * blockSize) + startingPositionY, blockSize,
                               blockSize};

                iconLocations[index].x1 = startingPositionX + blockSize + 1;
                iconLocations[index].x2 = (startingPositionX + blockSize + 1) + blockSize;
            }

            iconLocations[index].y1 = (index * blockSize) + startingPositionY;
            iconLocations[index].y2 = ((index * blockSize) + startingPositionY) + blockSize;

            // Icon background color
            SDL_SetRenderDrawColor(mainRender, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(mainRender, &outlineRect);

            SDL_RenderCopy(mainRender, texture, nullptr, &bitmapLayer);

            // Icon hover
            if (iconLocations[index].hover || iconLocations[index].selected) {
                SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(mainRender, &outlineRect);
            }

            index++;
        }
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void preLoadImages(){
    try {
        for (auto &icon: icons) {
            SDL_Surface *surface = IMG_ReadXPMFromArray((char **) icon);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(mainRender, surface);
            if (texture == nullptr) {
                spdlog::error("Unable to load image: {}\n", SDL_GetError());
            }
            SDL_FreeSurface(surface);
            textures.push_back(texture);
        }
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void drawStarFish(){
    auto *fish = new StarFish;
    fish->animation(mainRender, randomInteger(500), randomInteger(500), randomInteger(500), randomInteger(500));
}


void redrawMenu(){
    SDL_RenderSetViewport(mainRender, &mainMenu);
    drawRightMenuPane();
    drawIcons();
    drawColorOptions();
}

void redrawMainScreen(){
    SDL_RenderSetViewport(mainRender, &mainGrid);
    drawScreen();
    drawGrid();
}

void redraw(){
    SDL_SetRenderDrawColor(mainRender, 255,255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mainRender);
    redrawMainScreen();
    redrawMenu();
    drawStarFish();
    SDL_RenderPresent(mainRender);
}

void clearIconHover(){
    for (auto &iconLocation : iconLocations){
        iconLocation.hover = false;
    }
}

int iconHoverIndex(){
    int viewportOffset = maxScreenWidth - MENUWIDTH;
    clearIconHover();

    for (int i=0; i < iconLocations.size(); i++){
        if ((viewportOffset + iconLocations[i].x1 <= mouseLocation.x && mouseLocation.x <= viewportOffset + iconLocations[i].x2) &&
            (iconLocations[i].y1 <= mouseLocation.y && mouseLocation.y <= iconLocations[i].y2)) {
            return i;
        }
    }
    return -1;
}

void clearColorHover(){
    for (auto &colorLocation : colorLocations){
        for (auto &location : colorLocation){
            location.hover = false;
        }
    }
}

struct colorLocation colorHoverIndex(){
    int viewportOffset = maxScreenWidth - MENUWIDTH;
    clearColorHover();
    colorLocation location;

    for (int n = 0; n < colorLocations.size(); n++) {
        for (int m = 0; m < colorLocations[n].size(); m++) {
            if ((viewportOffset + colorLocations[n][m].x1 <= mouseLocation.x && mouseLocation.x <= viewportOffset + colorLocations[n][m].x2) &&
                (colorLocations[n][m].y1 <= mouseLocation.y && mouseLocation.y <= colorLocations[n][m].y2)) {
                location.n = n;
                location.m = m;
                return location;
            }
        }
    }
    return location;
}

void mouseEvents(){
    try {
        // Menu screen region
        if (mouseLocation.x > (maxScreenWidth - MENUWIDTH)) {
            // Hover
            if (!mouseLocation.clicked) {
                spdlog::info("RIGHT");

                // Hover icons
                int iconIndex = iconHoverIndex();
                if (iconIndex >= 0) {
                    spdlog::info("{}", iconIndex);
                    iconLocations[iconIndex].hover = true;
                    redrawMenu();
                }

                // Hover colors
                struct colorLocation colorIndex = colorHoverIndex();
                spdlog::info("{}, {}", colorIndex.n, colorIndex.m);
                if (colorIndex.n >= 0 || colorIndex.m >= 0) {
                    if (colorIndex.n < 0) {
                        colorIndex.n = 0;
                    }
                    colorLocations[colorIndex.n][colorIndex.m].hover = true;
                    SDL_Rect fillRect = {
                            colorLocations[colorIndex.n][colorIndex.m].x1,
                            colorLocations[colorIndex.n][colorIndex.m].y1,
                            colorLocations[colorIndex.n][colorIndex.m].x2 -
                            colorLocations[colorIndex.n][colorIndex.m].x1,
                            colorLocations[colorIndex.n][colorIndex.m].y2 -
                            colorLocations[colorIndex.n][colorIndex.m].y1
                    };

                    // Hover
                    SDL_SetRenderDrawColor(mainRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawRect(mainRender, &fillRect);
                    redrawMenu();
                }
            }
//            if (mouseLocation.clicked){
//                    // Click events
//                    if (iconIndex >= 0) {
//                        switch (iconIndex) {
//                            case 0:
//                                if (pixelSize <= 200) {
//                                    pixelSize += 1;
//                                }
//                                break;
//                            case 1:
//                                if (pixelSize >= 2) {
//                                    pixelSize -= 1;
//                                }
//                                break;
//                            case 2:
//                                showGrid = true;
//                                break;
//                            case 3:
//                                showGrid = false;
//                                break;
//                            case 8:
//                                ink = true;
//                                iconLocations[8].selected = true;
//                                iconLocations[9].selected = false;
//                                break;
//                            case 9:
//                                ink = false;
//                                iconLocations[8].selected = false;
//                                iconLocations[9].selected = true;
//                                break;
//                            default:
//                                break;
//                        }
//                    }
//                    if (colorIndex.n >= 0 || colorIndex.m >= 0){
//                        if (colorIndex.n < 0){
//                            colorIndex.n = 0;
//                        }
//                        if (ink) {
//                            selectedColors.ink = colorIndex.m;
//                        }
//                        else if (paper) {
//                            selectedColors.paper = colorIndex.m;
//                        }
//                        selectedColors.bright = (bool) colorIndex.n;
//                    }
//                }
//            }
        }

        // Main drawing region
        else {
            // Draw
            if (mouseLocation.clicked) {
                spdlog::info("LEFT");
                // Clicked on main board
                if (mouseLocation.x / pixelSize < pixels.size()) {
                    auto attr_copy = attributes[(mouseLocation.x / pixelSize) / 8][(mouseLocation.y / pixelSize) / 8];
                    if (ink) {
                        pixels[mouseLocation.x / pixelSize][mouseLocation.y / pixelSize] = true;
                        attributes[(mouseLocation.x / pixelSize) / 8][(mouseLocation.y / pixelSize) / 8] = {
                                selectedColors.ink,
                                attr_copy.paper,
                                selectedColors.bright
                        };
                    } else {
                        attributes[(mouseLocation.x / pixelSize) / 8][(mouseLocation.y / pixelSize) / 8] = {
                                attr_copy.ink,
                                selectedColors.paper,
                                attr_copy.bright
                        };
                    }
                }
            }
            else {

            }
        }
    }
    catch (std::exception &e){
        spdlog::error("{}, {}", e.what(), SDL_GetError());
    }
}

void resetAll(){
    ink = true;

    mainGrid = {0, 0, maxScreenWidth - MENUWIDTH, maxScreenHeight};
    mainMenu = {maxScreenWidth - MENUWIDTH, 0, MENUWIDTH, maxScreenHeight};

    // 256x192 (1x1) pixels
    pixels = {256, std::vector<bool>(192,false)};
    // 32x24 (8x8) attributes
    attributes = {32, std::vector<attribute>(24, {0, 7, true})};

    selectedColors = {0, 2, true};

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

    objectLocation location = {
            0,
            0,
            0,
            0,
            false,
            false
    };

    iconLocations = {10, location};
    iconLocations[8].selected = true;

    colorLocations = {colorPalette.size(), std::vector<objectLocation>(colorPalette[0].size(), location)};

    preLoadImages();

    redraw();
}

int main(int argc, char* args[]){
    try {
        if (!initSDL()) {
            spdlog::error("Error initializing SDL - {}", SDL_GetError());
        }
        else {
            SDL_Event e;
            SDL_ShowCursor(1);

            resetAll();

            bool mainLoopRunning = true;
            while (mainLoopRunning) {
                while (SDL_PollEvent(&e) != 0) {
                    // TODO: Please revisit. Several optimizations possible!
                    if (e.type == SDL_MOUSEBUTTONDOWN){
                        mouseLocation.clicked = true;
                        mouseEvents();
                    }

                    else if (e.type == SDL_MOUSEBUTTONUP){
                        mouseLocation.clicked = false;
                    }

                    else if (e.type == SDL_MOUSEMOTION){
                        SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
                        mouseEvents();
                    }

                    else if (e.type == SDL_WINDOWEVENT) {
                        if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                            maxScreenWidth = e.window.data1;
                            maxScreenHeight = e.window.data2;
                            mainGrid = {0, 0, maxScreenWidth - MENUWIDTH, maxScreenHeight};
                            mainMenu = {maxScreenWidth - MENUWIDTH, 0, MENUWIDTH, maxScreenHeight};
//                            redraw();
                        }
                    }

                    else if (e.type == SDL_KEYDOWN) {
                        spdlog::debug("key");
                    }

                    else if (e.type == SDL_QUIT) {
                        spdlog::info("SDL exiting");
                        mainLoopRunning = false;
                    }
                }
                redraw();
                SDL_Delay(1);
            }
        }

        exitSDL();
        return 0;
    }
    catch (const std::exception &e){
        spdlog::error("General error: {}\n\n{}", e.what(), SDL_GetError());
        exitSDL();
        return 1;
    }
}
