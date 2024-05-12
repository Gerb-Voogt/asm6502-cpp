# asm6502-cpp

## About the Project
This project is a collection of utility functions written in `C++` to facilitate working with 
6502 assembly code, and quickly assembling an dissassembling this code. Orginally, the purpose of this project
is to easily generate the raw binary data for test roms for checking if all CPU opcodes work as expected for a 
tangentially related nes emulator project.

## Getting Started
The following dependencies are required

- `cmake >= 3.10`
- `make`

To get started, clone the repository usign 

```bash
git clone git@github.com:Gerb-Voogt/asm6502-cpp.git
```

After this the project can be compiled using `cmake` and `make`:

```bash
mkdir build
cd build
cmake .. && make -j 4
```

then execute by running the following from the build directory

```bash
./asm6502
```

