# ZX-Paint

![Build](https://github.com/twelvechairssoftware/zxpaint/workflows/Build/badge.svg)
[![CodeQL](https://github.com/twelve-chairs/zxpaint/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/twelve-chairs/zxpaint/actions/workflows/github-code-scanning/codeql)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=twelve-chairs_zxpaint&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=twelve-chairs_zxpaint)

## Intro
An open source project to simulate the Sinclair ZX Spectrum's screen drawing capabilities, in the style of a simple modern-ish image manipulation editor! Includes realistic pixel dimensions, and proper attribute-based colour schemes. Why? Simply because the [ZX Spectrum](https://en.wikipedia.org/wiki/ZX_Spectrum) is a unique monster from the 80s that has had such a massive impact on gaming, and demo scenes with its [quirky screen drawing capabilities](https://en.wikipedia.org/wiki/ZX_Spectrum_graphic_modes). Even more honestly - we just wanted to become more familiar with `SDL2` to enhance our skillset for future cross-platform game and simulation software, and just happen to be huge Speccy fans! This is no DPaint, but we hope that other Speccy enthusiasts will enjoy this, too 😊

![Screenshot](https://github.com/twelvechairssoftware/zxpaint/raw/master/res/zxpaint.png)

## Roadmap
1. Basic pixels ✅
2. Window resizing ✅
3. Basic zoom in/out ✅
4. Menu selector buttons (hover and click) ✅
5. Attributes ✅
6. Color/ink/paper selection ✅
7. View panning (maybe scroll bars) 🌤️
8. Basic shapes (line, circle) 🌤️
9. Shape filling 🌤️
10. Text 🌤️
11. Save to file 🌤️
12. Export to `scr` 🌤

✅ - done; 🚧 - in-progress; 🌤️ -  some day, maybe;

## Open source libraries used:
 - SDL2 (https://www.libsdl.org)
 - spdlog (https://github.com/gabime/spdlog)

## Installation
Ubuntu (x86), Raspberry Pi (armv7l)
```shell
sudo apt-get update -y
sudo apt-get install -y build-essential libspdlog-dev git cmake curl libsdl2-2.0 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```
Fedora
```shell
dnf groupinstall "Development Tools" -y
sudo dnf update -y
sudo dnf install -y cmake spdlog SDL2 SDL2-devel SDL2_image SDL2_image-devel SDL2_ttf SDL2_ttf-devel
```
MacOS
```shell
sudo xcode-select --install
brew install python cmake spdlog sdl2 sdl2_image sdl2_ttf
```

All 
```shell
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -G "CodeBlocks - Unix Makefiles" .
cmake --build . --target ios -- -j 2
./bin/ios &
```

Windows 10
```shell
COMING SOON
 ```
