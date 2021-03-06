#! /bin/bash


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
