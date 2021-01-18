source ~/.bashrc

conan profile new default --detect
conan profile update settings.compiler.libcxx=libc++ default
conan install .

mkdir cmake-build-minsizerel

cmake -DCMAKE_BUILD_TYPE=MinSizeRel -G "CodeBlocks - Unix Makefiles" .

cmake --build . --target zxpaint -- -j 2
