# Kx
A collection of libraries and clients. Intended to be a game engine and game client at some point.


## FRONTEND (CLIENTS)

# Kremonte_Engine
Note: If building a fresh version of this library, make sure that glfw is properly built.

To build and run Kremonte_Engine:
	1. Open in VS
	2. Run CMake generation (e.g save a CMakeLists.txt file to auto-trigger)
	3. Run Kremonte_Engine.exe


## BACKEND

# Kremonte
A game-engine library.

# KxGUI
A lightweight version of the Kremonte library that can be used for building launchers and other
applications that don't require a full game-engine backend.

# KRASKA
Intended to be a novel visual computation system. Planned as a game mechanic as well.


# How-To
Change a git submodule:
	1. git submodule set-url <deps/submodule> <url>
	2. git submodule update --init --recursive --remote

Build GLFW in Debug mode:
	1. cd deps/glfw
	2. run the following commands: 
		cmake -S . -B build -D BUILD_SHARED_LIBS=ON
		cmake --build build --config Debug
	3. Find glfw3.dll and rename it to glfw3d.dll
	4. Set the GLFW path in the root CMakeLists.txt to the location of this .dll