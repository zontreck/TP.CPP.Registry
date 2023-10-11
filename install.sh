#!/bin/bash

mkdir build
pushd build

cmake ..
make
sudo make install

popd
