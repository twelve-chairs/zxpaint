source ~/.bashrc

conan profile new default --detect
#MacOS doesn't recognize libstdc++11, so do this instead
conan profile update settings.compiler.libcxx=libc++ default
conan install .

mkdir cmake-build-minsizerel

cmake -DCMAKE_BUILD_TYPE=MinSizeRel -G "CodeBlocks - Unix Makefiles" .

cmake --build . --target zxpaint -- -j 2
