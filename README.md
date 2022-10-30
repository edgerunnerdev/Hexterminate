# HEXTERMINATE

## Table of contents

- 1.0 [About](#10-about)
    - 1.1 [Supported platforms](#11-supported-platforms]
    - 1.2 [Hardware requirements](#12-hardware-requirements]
    - 1.3 [Getting the game](#13-getting-the-game]

## 1.0) About

HEXTERMINATE is an open-source top-down shooter which puts you in the role of an Imperial Captain with the mission of reclaiming a galaxy shattered by centuries of in-fighting. You customise your ship with dozens of different modules, fight side by side with allied fleets and reunite the galaxy under Imperial rule.

## 1.1) Supported platforms

- Windows 10 and 11, 64 bits. Older versions of Windows will likely work but haven't been tested.
- Linux, 64 bits. Tested against Linux Mint 20.2 Cinnamon. Other distributions (particularly Debian-based) are likely to work without changes.

## 1.2) Hardware requirements

- Processor: Interl(R) Core(TM) i5-2500 CPU @ 3.30GHz
- Memory: 8 GB RAM
- Graphics: NVIDIA GeForce GTX 1850 Ti

## 1.3) Getting the game

Currently the game can be bought from [Steam](https://store.steampowered.com/app/1123230/HEXTERMINATE/), but is an older version which is Windows-only.

The latest version, which is still in development, must be built from source.

## Checking out the project
Run `git clone --recurse-submodules https://github.com/edgerunnerdev/Hyperscape.git`

## Building on Windows

- Install Visual Studio 2022 (you can use the [Community edition](https://visualstudio.microsoft.com/vs/community/)).

## Building on Linux

### Requirements

You'll need *clang* and *cmake*

You'll need to install the following packages:
sudo apt install clang cmake libsdl2-dev libsdl2-image-dev libbullet-dev libglew-dev libvpx-dev libsdl2-mixer-dev
