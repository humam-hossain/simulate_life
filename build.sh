#!/bin/sh

set -xe
# g++ -Wall -Wextra -o main main.cpp -lm
g++ -Wall -Wextra -o smoothlife_gpu smoothlife_gpu.cpp -lm -lraylib -lGL -ldl -lrt -lX11 -lpthread