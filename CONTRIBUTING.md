# Contributing to Vulkan-Example

Thank you for your interest in contributing!

## How to Contribute

1. **Fork** the repository and create a new branch for your changes.
2. **Clone** your fork:
   ```sh
   git clone https://github.com/<your-username>/Vulkan-Example.git
   cd Vulkan-Example
   ```
3. Make sure your code follows the project’s code style (see below).
4. Open a Pull Request to the `main` branch with a clear description of your changes.

## Code Style

- **camelCase**: function names, method names, function arguments, local variables  
- **UPPER_CASE**: constants, enum values, macro definitions  
- **snake_case**: file names, namespaces  
- **m_ + PascalCase**: class members  
- **PascalCase**: class, struct, type, and enum names  
- **PascalCase + T**: template names  
- Use only `.h` and `.cpp` file extensions  
- Use `auto` minimally  
- All header files must start with `#pragma once`  
- Use `const` or `constexpr` for variables that do not change  
- Braces must not be on separate lines  
- Fragment shaders: `.frag` extension; Vertex shaders: `.vert` extension

If you have any questions, open an [issue](https://github.com/rikzun/Vulkan-Example/issues) or start a discussion.  
Thank you for contributing!