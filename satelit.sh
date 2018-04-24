#!/bin/bash/

cd /mnt/c/Users/lorenz/source/repos/ode

if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
else
    cd build
fi

make -j satelit
./satelit
cd ..
python satelit.py
cd ..
