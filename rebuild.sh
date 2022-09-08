#!/bin/bash -e

find . ! \( -name rebuild.sh -or -name '.' \) -exec rm -rf {} \;
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j6 
