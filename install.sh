#!/bin/bash

set -e

cd build

sudo make install 

cd ..

# Restart krunner for the changes to take effect

kquitapp5 krunner
krunner &


