#!/bin/bash

set -e

if [ -d build ]; then
	rm -rf build
fi
mkdir build
cd build

cmake .. -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) -DQT_PLUGIN_INSTALL_DIR=$(kf5-config --qt-plugins)
make 

cd ..

