
Installation instructions
=========================

Ubuntu
------

Create a build subdirectory (mkdir build) -> go there and call cmake with the parent dir as argument
(where the main CMakeLists.txt is located)

```
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

Install [https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=Community&rel=15](Visual Studio Community Edition)

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
