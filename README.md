
Installation instructions
=========================

Ubuntu
------

Install the needed dependencies:

``` bash
sudo apt install libglu1-mesa-dev python3 cmake git freeglut3-dev
```
Clone the git repository:

``` bash
git clone https://data.asc.tuwien.ac.at/jschoeberl/ode.git
```
Go to the folder and create a build subdirectory -> go there and call cmake with the
parent dir as argument (where the main CMakeLists.txt is located)

```
cd ode
mkdir build
cd build
cmake ..
```

then call
```
make -j
```
to compile your code. The executables are located in the respective paths of the build folder.

Start coding :)


Windows
-------

Install [Visual Studio Community Edition](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=Community&rel=15)

While installing check the options for

Workloads -> "Desktop development with C++", "Python development" "Linux C++ Development Tools"

Individual components -> "Git for Windows", "Visual C++ tools for CMake and Linux"

Start Visual Studio
go to Team -> Manage Connections -> Git -> Clone

enter url: https://data.asc.tuwien.ac.at/jschoeberl/ode.git

In the team explorer tab -> Connect -> Branches -> release -> fetch

Copy the location of the folder by selecting "Show folder view" and then copying the path. In VS go
to File -> Open -> Folder

paste the folder and open it. VS should now start to recognize the cmake file and add a CMake item to
the toolbar at the top.

First change the build type from x86-Debug to x64-Debug, then go CMake -> "Build All",
then CMake -> Install -> ode.

Now your project is built and installed and you can run the examples by selecting the file in the
"Select Startup Item" dropdown menu and click play. Always select the Install version of the target!
