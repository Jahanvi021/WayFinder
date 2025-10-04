🚗 PathFinder (A* Route Planning Project)

This repository contains the A* Route Planning project, built in C++ using the IO2D graphics library.
It finds the shortest path between two points on a real OpenStreetMap (OSM) using the A* algorithm.

<img src="map.png" width="600" height="450" />
🔁 Cloning

When cloning this project, be sure to use the --recurse-submodules flag.

Using HTTPS:
git clone https://github.com/Jahanvi021/PathFinder.git --recurse-submodules

Using SSH:
git clone git@github.com:Jahanvi021/PathFinder.git --recurse-submodules

⚙️ Dependencies for Running Locally

cmake >= 3.11.3
🔗 Installation Instructions

make >= 4.1 (Linux, Mac), 3.81 (Windows)

Linux: pre-installed

Mac: install via Xcode Command Line Tools

Windows: Download Here

gcc/g++ >= 7.4.0

Linux: pre-installed

Mac: install via Xcode Command Line Tools

Windows: recommended MinGW

IO2D Graphics Library
🔗 Installation Guide

🧱 Compiling and Running
1️⃣ Create a Build Directory
mkdir build && cd build

2️⃣ Run CMake and Make
cmake ..
make

▶️ Running the Project

Run from inside the build folder:

./PathFinder


Or specify a custom OSM map file:

./PathFinder -f ../<your_map_file.osm>

🧪 Running Tests

From inside the build directory:

./test

🛠 Troubleshooting
🧩 IO2D Installation Issues

Make sure you have downloaded and built this repo
.

For Mac users:

Comment these lines in CMakeLists.txt under P0267_RefImpl:

if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
     add_subdirectory(P0267_RefImpl/Samples)
endif()


Then run "ALL_Build" and "install" in Xcode.

If packages are missing:

brew install pkg-config

🐧 Ubuntu Linux Setup
sudo apt update
sudo apt install build-essential cmake libcairo2-dev libgraphicsmagick1-dev libpng-dev

git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug && cd Debug
cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
cmake --build .
sudo make install

🪟 Windows Users

If you face issues with IO2D installation:

Enable WSL (Windows Subsystem for Linux)

Install Ubuntu from the Windows Store

Install all dependencies inside WSL

Configure your IDE (e.g. CLion) to use the WSL toolchain

More help: GitHub Issue Thread

💡 If you see errors with --config, try removing -- from the command.

👤 About the Author

Made with ❤️ by Jahanvi021
