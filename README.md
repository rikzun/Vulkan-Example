# Vulkan-Example

Sample Vulkan application using SDL3.

## Description

This project demonstrates basic Vulkan initialization, window management with SDL3, event handling, and structured logging. It is intended as a starting point for your own Vulkan experiments.

## Quick Start

### Requirements

- CMake 3.29+
- **clang** compiler with C++23 support
- Vulkan SDK
- Git

*Recommended: clangd for code navigation and inline diagnostics.*

## Build

The project uses [CMake Presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html).  
Choose a preset for your OS and build type:

**For Linux:**
```sh
cmake --preset linux-debug
cmake --build --preset linux-debug (or linux-release)
```

**For Windows:**
```sh
cmake --preset win-debug
cmake --build --preset win-debug (or win-release)
```

All build artifacts will be placed in the `output/<preset>` directory.

#### Notes

- On Windows, run from the directory with the executable so shaders can be found.
- If the app does not start, ensure you have the Vulkan SDK and up-to-date GPU drivers.

## How to Contribute

See [CONTRIBUTING.md](./CONTRIBUTING.md).

## License

MIT License (see [LICENSE](./LICENSE))