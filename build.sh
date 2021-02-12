conan profile new default --detect

if [ "$(uname)" == "Darwin" ]; then
  conan profile update settings.compiler.libcxx=libc++ default
  conan install .
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  conan profile update settings.compiler.libcxx=libstdc++11 default
  conan install . --build=spdlog --build=fmt
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under 32 bits Windows NT platform
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
fi

mkdir cmake-build-minsizerel

cmake -DCMAKE_BUILD_TYPE=MinSizeRel -G "CodeBlocks - Unix Makefiles" .

cmake --build . --target zxpaint -- -j 2
