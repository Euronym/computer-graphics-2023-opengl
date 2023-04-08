#/bin/bash

g++ main.cpp -I "./irrKlang-64bit-1.6.0/include" -L "/usr/lib" ./irrKlang-64bit-1.6.0/bin/linux-gcc-64/libIrrKlang.so -I include -o main -lGL -lGLU -lglut -lm -pthread