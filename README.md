## Windows:

### Pre-requisites

1. Install https://www.msys2.org/
1. Install toolchain:
   ```
   pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
   pacman -S mingw-w64-x86_64-cmake
   pacman -S git
   ```
1. Update path to include C:\msys64\ucrt\bin, C:\msys64\mingw64\bin, “C:\msys64\usr\bin.
1. Install libraries:
   ```
   pacman -S mingw-w64-x86_64-SDL2
   pacman -S mingw-w64-x86_64-SDL2_ttf
   pacman -S mingw-w64-x86_64-boost
   ```

### Build

From cloned repo, run:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

If successful, you have a runnable .exe.