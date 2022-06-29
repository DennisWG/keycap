# keycap

All purpose cross-platform library providing a number of different modules for my every day projects.

# Installation

Download an compile [Botan3](https://github.com/randombit/botan). When running CMake, make sure to populate the variables `Botan3_DIR_INCLUDE` (Path\To\Botan\include\botan-3) and `Botan3_DIR_LIB` (Path\To\Botan\lib) respectively.

You may now link against the various `keycap::*` modules.

# Modules

## keycap.core

Core components that may be used within other modules. 

## keycap.window

Provides the ability to create windows. Currently used only as a surface to render into using APIs like OpenGL or Vulkan.

## keycap.crypto

A nice wrapper around [Botan3](https://github.com/randombit/botan). Remember: Never run your own crypto code unless you're a domain expert!
