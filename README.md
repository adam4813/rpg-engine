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


## Documentation
Documentation is done via Doxygen for C++ code and supplementary docs must be maintained for the Lua API in the docs/ folder.

Whenever there is a Lua API change please update the corresponding docs/.

### Local Preview
To preview the Lua API docs locally visit [MkDocs](https://www.mkdocs.org/getting-started/) and follow their setup guide. Then from the root directory run `mkdocs serve`.
