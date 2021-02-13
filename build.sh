conan profile new default --detect

if [ "$(uname)" == "Darwin" ]; then
  echo "Darwin detected"
  conan profile update settings.compiler.libcxx=libc++ default

elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  echo "Linux detected"
  conan profile update settings.compiler.libcxx=libstdc++11 default

elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
  # Do something under 32 bits Windows NT platform
  echo "WIN32 Detected"

elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
  # Do something under 64 bits Windows NT platform
  echo "WIN64 Detected"

else
  # Default
  echo "Unable to detect platform"
fi

conan install . --build=spdlog --build=fmt

mkdir cmake-build-minsizerel

cmake -DCMAKE_BUILD_TYPE=MinSizeRel -G "CodeBlocks - Unix Makefiles" .

cmake --build . --target zxpaint -- -j 2
