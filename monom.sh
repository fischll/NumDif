#! /bin/bash

echo Maximaler Polynomgrad der p-Fem:
read polynomgrad

if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
else
    cd build
fi

make -j monom
./monom $polynomgrad
cd ../plot
python monom.py
