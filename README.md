# miniRT

A small ray tracer project from 42 that implements a minimal real-time renderer capable of parsing scene files and rendering basic primitives (spheres, planes, cylinders, lights, camera) using ray tracing principles. This repository contains the source code, example scenes and assets.

## Table of contents
- About
- Features
- Requirements
- Build & installation
  - Dependencies
  - Build
- Usage
- Scenes & screenshots
- Project structure
- Coding style & testing

## About
miniRT is a compact educational ray tracer that demonstrates:
- Scene parsing from simple text files
- Ray-object intersection for common primitives
- Lighting (ambient, point lights), shadows etc
- An interactive view window (using MiniLibX)

This project follows the 42 pedagogical constraints and focuses on clarity and correctness.

## Features
- Parse scene files (.rt) describing camera, lights and objects
- Render spheres, planes, and cylinders
- Shadows
- View window via MiniLibX

## Requirements
- A POSIX-compatible environment (Linux or macOS)
- C compiler (gcc or clang)
- Make
- MiniLibX (the version matching your OS)
- Optional: libX11 / X11 development headers on Linux

## Installation / Build

1. Clone the repository in a recursive way
   git clone -- recursive https://github.com/Loufok0/miniRT.git
   cd miniRT

2. Install dependencies
   - On macOS:
     - Install Xcode command line tools
     - Install MiniLibX for macOS (follow the 42 MiniLibX instructions)
   - On Linux (X11):
     - Install libx11-dev, libxext-dev, libbsd-dev (package names depend on distro)
     - Build or install MiniLibX for X11

3. Build
   - Typical Makefile targets (adapt if your Makefile uses different names):
     make        # build the project
     make clean  # remove object files
     make fclean # remove binary and object files
     make re     # fclean then make

   Example:
   make
   ./miniRT maps/test.rt

Notes:
- If MiniLibX is installed in a nonstandard location, edit the Makefile to adjust include and library paths.
- On macOS you may need to link with -framework OpenGL -framework AppKit depending on your MiniLibX setup.

## Usage
Run the program with a scene file:
./miniRT maps/burger.rt

Common behavior:
- Opens a window
- Loading bar appear in the terminal
- Displays the rendered scene
- Repeat the operation mutiple times to reduce the noise and enhance the quality

## Scenes & Screenshots
<img src="https://github.com/Loufok0/miniRT/blob/main/ressources/Pokeball.png" width="500">)
<img src="https://github.com/Loufok0/miniRT/blob/main/ressources/Burger.webp" width="500">)

## Project structure (suggested)
- src/            — execution, calculs and rendering code
- includes/       — headers
- maps/         — example .rt scene files
- parsing/      — parsing code
- Makefile
- README.md

## Coding style & tests
- Follow 42 school coding standards (norminette)
- Use Valgrind or similar tools to check for memory leaks:
  valgrind --leak-check=full ./miniRT maps/test.rt 
  (I recommend reducing all the defined values in the header, since it'll take an eternity to render the image with valgrind... )
