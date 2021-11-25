# Path-Tracing Renderer

This project renders images using [Path-Tracing](https://en.wikipedia.org/wiki/Path_tracing).

## Features

### Implemented

- Naive Lighting Strategy
- [Netpbm Image Format](https://en.wikipedia.org/wiki/Netpbm#File_formats)
  - Portable FloatMap (`*.pfm`)
    - HDR (no tonemapping, for editing afterwards)
    - RGB32F
  - Portable PixMap (`*.ppm`)
    - SDR (built-in exposure tonemap)
    - RGB8
- Ray-Marching
  - [Signed Distance Function (SDF) Rendering](https://en.wikipedia.org/wiki/Signed_distance_function)
- Support for Bidirectional Scattering Distribution Functions
  - Lambertian BRDF included

### TODO

- Better camera system
  - Optional camera mechanics simulation
    - Lens dynamics, e.g. focal length, aperature, distortion
- Bidirectional Path-Tracing
  - Optional, since it isn't good for all scenarios
- Bounding Volume Hierarchy (BVH)
  - Will allow for rendering meshes
- CPU + Vulkan render device integration
  - Vulkan only avaiable as a compile option for easier compilation for users who don't need Vulkan support
- Multiple Importance Sampling (MIS)
- Next Event Estimation (NEE)
- Spectral rendering?
  - This repository isn't gonna be fit for scientific use for a long time
- Variable scenes without re-compiling
- Variable settings without re-compiling

## Compiling

> This section is under construction

### Notices

#### GLM

> We are now using [GLM (OpenGL Mathematics)](https://github.com/g-truc/glm) which makes compiling a little bit more difficult. While custom vector math was fun and easy to compile since everything came with the repository, it wasn't very practical for development...

#### Vulkan

> Right now the Vulkan version of the renderer utilizes the Vulkan SDK. It's not very easy to set up for cross-platform and having a compile option to enable/disable it for easier compilation is on the TODO.

This guide will not go over compiling with Vulkan, since it's kinda complicated at the moment. Expect that to change in the future.

### General Cross-Platform

If you want to bring your own compiler, first make sure you have [GLM](https://github.com/g-truc/glm) installed. Then, add the following files to your compiler's input:

- `[repository]/src/main.cpp`
- `[repository]/src/image.cpp`
- `[repository]/src/path-tracing.cpp`
- `[repository]/src/rng.cpp`
- `[repository]/src/scene.cpp`
- `[repository]/src/sky.cpp`
- `[repository]/src/trace.cpp`

Finally, make sure you include `[repository]/src/include`.

### Linux (GCC)

To compile this project on a Debian-based Linux system using [GCC (GNU Compiler Collection)](https://gcc.gnu.org/), just make sure you have it installed. If you don't know if you have it, you can install it by running:

```sh
sudo apt install build-essential
```

If [GCC](https://gcc.gnu.org/) is already installed, apt will either say you have the latest version or tell you an upgrade is available. Now, make sure you have [GLM](https://github.com/g-truc/glm) installed. If you don't know if you have it, you can install it by runnning:

```sh
sudo apt install libglm-dev
```

Once you have [GLM](https://github.com/g-truc/glm), you can compile the project by running the build script:

```bash
build.sh
```

You should now be able to run the executable `OpenPT` simply by using:

```bash
./OpenPT
```

### Windows (Mingw-w64)

To compile this project on a Windows system using [Mingw-w64](https://www.mingw-w64.org/), just make sure you have it installed. If you don't have it, you can get it at <https://www.mingw-w64.org/downloads/>. Now, make sure you grab the latest release of [GLM](https://github.com/g-truc/glm). If you don't have it, you can get it at <https://github.com/g-truc/glm>. Once you have downloaded the latest release of [GLM](https://github.com/g-truc/glm), extract the archive and rename the folder it creates to `glm`. You can now compile the project by running the build script:

```cmd
build.bat
```

You should now be able to run the executable `OpenPT.exe` from File Explorer, or simply by using:

```cmd
OpenPT.exe
```

### MacOS

MacOS is not and will not be officially supported. You will just have to test bring your own compiler and test your luck. There is no official MacOS support because I ([@Zi7ar21](https://github.com/Zi7ar21)) do not have access to a Mac and have no interest in getting one because Apple's ecosystem is absolutely proprietary and cringe. Normally I would just disregard Mac support entirely but if you do have an issue running this then you can submit an issue and I _might_ fix it.

## Running

At this time there isn't any command-line arguments. You can just run the executable (either `OpenPT` or `OpenPT.exe`) and it will render the scene.

## Linux

```bash
./OpenPT
```

If the executable isn't already marked as an executable, run:

```bash
sudo chmod +x ./OpenPT
```

## Windows

Double-click `OpenPT.exe` in File Explorer, or run:

```cd
OpenPT.exe
```
