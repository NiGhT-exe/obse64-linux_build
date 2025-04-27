![testbuild](https://github.com/ianpatt/obse64/workflows/testbuild/badge.svg)

# OBSE64 - build files on a GNU/Linux system

Linux-compatible fork of [OBSE64](https://github.com/ianpatt/obse64) (Oblivion Script Extender for Oblivion Remastered).

## Prerequisites

Install required packages:
```bash
yay -S mingw-w64-gcc mingw-w64-binutils mingw-w64-headers mingw-w64-crt mingw-w64-winpthreads cmake make
```

## Building

Run the included build script:
```bash
git clone https://github.com/NiGhT-exe/obse64-linux_build.git
cd obse64-linux_build
./build.sh
```

This will configure the project with the included MinGW toolchain and build the binaries.

## Running with Wine

1. Copy the built DLL and EXE files:
   ```
   build/obse64/libobse64_0_411_140.dll
   build/obse64_loader/obse64_loader.exe
   ```
to your Oblivion installation, this is usually C:\Program Files\Steam\SteamApps\common\Oblivion Remastered\OblivionRemastered\Binaries\Win64.

2. Launch the game by running obse64_loader.exe.

## Runtime Support
OBSE64 supports the latest version of Oblivion Remastered on Steam. The MS Store/Gamepass version is not supported.
