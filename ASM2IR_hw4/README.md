## Simple Simulator implementation:
The ISA description is placed in the `include/ISA.h`.

Application needs 2 argument: file with assembler and execution mod (1-3):
1. Simulation
2. IR with emulate funcs
3. Full IR generation
```
clang++ $(llvm-config --cppflags --ldflags --libs) *.cpp ../graphic_app_hw1/SDL/sim.c -I ../SDL -lSDL2
./a.out app.sim 1
./a.out app.sim 2
./a.out app.sim 3
```

Added Stack
