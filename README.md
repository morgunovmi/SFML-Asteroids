# SFML-Asteroids
Simple asteroids clone game written with SFML.

![sc](https://user-images.githubusercontent.com/48750724/169696335-627b4e5d-afcd-4c9a-9ad8-22bb4f52d612.png)

## Playing

If you just want to play the game, you can download it on the Releases page of this repo. (Only windows binary is now available)

## Build

These build instructions are for a release build and assume you have Cmake installed, have vcpkg in path-to-vcpkg.
Steps for Windows(x64):

```
git clone https://github.com/morgunovmi/SFML-Asteroids.git
cd SFML-Asteroids
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=path-to-vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
cmake --build . --config=Release
..\bin\Release\Release\AsteroidsApp.exe
```

Steps for Linux(x64):

```
git clone https://github.com/morgunovmi/SFML-Asteroids.git
cd SFML-Asteroids
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=path-to-vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux ..
cmake --build .
..\bin\Release\AsteroidsApp.exe
```
