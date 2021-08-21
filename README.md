# Path-Tracing Renderer

This repository contains the source code for The Order of the Simulation community Path-Tracing Renderer.

## Compiling

Currently the CPU and Vulkan renderers are seperate. There is plans in the future to merge them into one program that can select either device and render the same scene.

### Windows

This will walk you through compiling this project on a Windows 10 (or possibly later) machine using Visual Studio.

---

#### Vulkan

After installing [Visual Studio](https://visualstudio.microsoft.com/) and [VulkanSDK](https://vulkan.lunarg.com/sdk/home#windows), open `CMakeLists.txt` in Visual Studio.


### Linux

This will walk you through compiling this project on a Debian-based distro (e.g. Ubuntu) using Make and GCC/Clang.

---

#### CPU

First install `build-essential` by running:

```sh
sudo apt install build-essential
```

Then enter the CPU directory by running

```sh
cd cpu
```

Finally, compile the project by running

```sh
make
```
