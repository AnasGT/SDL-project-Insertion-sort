# SDL Workshop 💻

## Overview

Welcome to the SDL Workshop! This repository contains resources and examples to help you get started with Simple DirectMedia Layer (SDL), a cross-platform development library designed to provide low-level access to audio, keyboard, mouse, and display functions.

## Contents

1. [Getting Started](#getting-started)
2. [Prerequisites](#prerequisites)
3. [Installation](#installation)
4. [Documentation](#documentation)
5. [Contributing](#contributing)

## Getting Started 🚀

To begin with the SDL Workshop, follow these steps:

### Prerequisites

Before you start, ensure you have the following installed on your system:

GCC:
- [C/C++ Compiler](https://gcc.gnu.org/install/index.html)

### Installation

1. Clone this repository:

    ```bash
    git clone https://github.com/yasuogg/sdl-workshop.git
    ```

2. Build the examples using your preferred build system.

## RUN CODE

windows:

```bash
mingw32-make -f Makefile
```
Mac:
```bash
gcc -o main src/main.c -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf && ./main
```
## Documentation

Refer to the [official SDL documentation](https://wiki.libsdl.org/) for detailed information on SDL functions, structures, and usage.

## Contributing

If you find any issues or have suggestions for improvement, feel free to open an issue or submit a pull request. Contributions are welcome!

Happy coding!
