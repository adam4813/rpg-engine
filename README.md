# RPG Game
Moderm (C++17/20) game engine for learning.


## Minimum Compiler Versions
The following [compilers support](https://en.cppreference.com/w/cpp/compiler_support) the few C++20 features that are being used
* GNU (gcc/g++) - 10
* Clang - 13
* AppleClang - 13.1.6 (XCode 13.3) **Requires MacOS 12**
* MSVC - 19.25 (Visual Studio 2019 16.5)

### C++20 Features of Note
* `std::jthread` and `std::stop_token`
* `std::bind_front`

## Dependencies:
* [cmake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)
* [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) ***Optional***

### Linux / WSL
Dependencies:
* `gcc10 g++10` or `clang-13`
* `build-essentials pkg-config tar curl zip unzip gdb`
* `libgl1-mesa-dev xorg-dev libglu1-mesa-dev libxinerama-dev libxcursor-dev p7zip-full`

## Supported editor(s)
* Visual Studio
* Visual Studio (CMake folder mode)
  * Change Tools -> Options -> CMake -> General and enable "Prefer using CMake Presets..."
* Visual Studio Code
  * On Windows you may need to add the CMake bin directory to path, for CTest to work.
* CLion
  * Not tested, but CMake folder mode should work as expected


## Documentation
Documentation is done via Doxygen for C++ code and supplementary docs must be maintained for the Lua API in the docs/ folder.

Whenever there is a Lua API change please update the corresponding docs/.

### Local Preview
To preview the Lua API docs locally visit [MkDocs](https://www.mkdocs.org/getting-started/) and follow their setup guide. Then from the root directory run `mkdocs serve`.
