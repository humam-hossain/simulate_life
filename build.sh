#!/bin/sh

set -xe
# g++ -Wall -Wextra -o main main.cpp -lm
g++ -Wall -Wextra -o smoothlife_gpu smoothlife_gpu.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11