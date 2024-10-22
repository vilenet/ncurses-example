# ncurses-example


g++ main.cpp -o main.exe -IC:\msys64\mingw32\include -LC:\msys64\mingw32\lib -lpdcurses


Cmake:

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
