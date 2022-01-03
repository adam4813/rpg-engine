# RPG Game

## Setup
All platforms will need to have the following installed
Dependencies:
* [cmake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)

### Windows
Dependencies:
* [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) ***Optional***

Supported editor(s)
* Visual Studio
* Visual Studio (CMake folder mode)
  * Change Tools -> Options -> CMake -> General and enable "Prefer using CMake Presets..."
* Visual Studio Code
  * CTest may not discover tests

### Linux / WSL
Dependencies:
* `gcc9 g++9`
* `build-essentials pkg-config tar curl zip unzip gdb`
* [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)
* `libgl1-mesa-dev xorg-dev libglu1-mesa-dev libxinerama-dev libxcursor-dev p7zip-full`
