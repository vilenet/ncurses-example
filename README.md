# ncurses-example

PDCurses examples

Build by hand in cmd:
g++ main.cpp -o main.exe -IC:\msys64\mingw32\include -LC:\msys64\mingw32\lib -lpdcurses


Build Cmake:

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
