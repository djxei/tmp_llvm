#!/bin/bash

clang++ Pass_trace.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

mkdir -p tmp

clang -O1 -fpass-plugin=./libPass.so -c ../graphic_app_hw1/app.c -o tmp/app.o

clang log.c tmp/app.o ../graphic_app_hw1/sim.c ../graphic_app_hw1/start.c -lSDL2 -o tmp/a.out && timeout 1s ./tmp/a.out 

rm -rf tmp
