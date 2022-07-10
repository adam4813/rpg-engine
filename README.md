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

## Build Dependencies:
* [cmake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)
* [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) ***Optional***

## Linux / WSL Dependencies
* `gcc10 g++10` or `clang-13`
* `build-essentials pkg-config tar curl zip unzip gdb`
* `libgl1-mesa-dev xorg-dev libglu1-mesa-dev libxinerama-dev libxcursor-dev p7zip-full`

## Supported editor(s)
* Visual Studio
* Visual Studio (CMake folder mode)
  * Change Tools -> Options -> CMake -> General and enable "Prefer using CMake Presets..."
* Visual Studio Code
  * On Windows you may need to add the CMake bin to the system path, for CTest to work.
* CLion
  * Not tested, but CMake folder mode should work as expected

# Targets
## Config:
* `ninja-multi-vcpkg` - Ninja multi-build config preset that references the vcpkg toolchain file relative to the `VCPKG_ROOT`
  
## Build:
* `ninja-multi-vcpkg-debug` - Debug configuration build preset that uses the `ninja-multi-vcpkg` config
* `ninja-multi-vcpkg-release-dbginfo` - Release with debug info configuration build preset that uses the `ninja-multi-vcpkg` config
* `ninja-multi-vcpkg-release` - Release configuration build preset that uses the `ninja-multi-vcpkg` config
* `verbose-build` - Verbose build preset that uses the `ninja-multi-vcpkg` config
* `ninja-multi-docs` - Doc build preset with the documentation custom [targets](#documentation-targets)

## Test
* `test-base` - Base test preset that all other tests derive from **DO NOT USE**
* `ninja-multi-vcpkg-debug` - Debug configuration test preset
* `ninja-multi-vcpkg-release` - Release configuration test preset

# Documentation
Documentation is done via Doxygen for C++ code and supplementary docs must be maintained for the Lua API in `docs/`.

Engine documentation is generated with the with the `ninja-multi-docs` build config `doxygen` target, and is then
ed convert to markdown via `doxybook2` with the `ninja-multi-docs` build config `doxybook` target.

All documentation is converted to mkdocs format with the `ninja-multi-docs` build config `mkdocs` target, and then
readthedocs hosts the mkdocs files.

Doxygen and mkdocs files **are not** committed, but can be generated locally for consumption/validation. Doxybook
generated docs and all other docs in `docs/` **are** committed.

## Documentation Dependencies
* [doxygen](https://www.doxygen.nl/) 1.9.4
* [doxybook2](https://github.com/matusnovak/doxybook2) 1.4.0
* [python](https://www.python.org/) 3.10.4 (Earlier version may work, but untested)
* [pip](https://pip.pypa.io/en/stable/) 22.0.4 (Earlier version may work, but untested)
* [pip-tools](https://github.com/jazzband/pip-tools) 6.8.0 (Earlier version may work, but untested)
* [mkdocs](https://www.mkdocs.org/) 1.3.0 (see docs/requirements)

## Readthedocs setup
To generate the python requirements for mkdocs to be used by readthedoc run `pip-compile docs/requirements.in` in the project root.

## Documentation Targets
The following targets can be built when the CMake build preset is set to `ninja-multi-docs`

* doxygen - Generates full doxygen docs in `doxygen/` 
* doxybook - Generates markdown versions of doxygen docs and places them in `docs/engine/`
* mkdocs - Generates mkdocs from `docs/` in places them `mkdocs/`

## Local Preview
To preview the mkdocs docs locally visit run `mkdocs serve`, in the project root.
