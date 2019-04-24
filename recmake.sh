#!/bin/bash
rm -r build/
#sudo rm -r lib/*
#sudo rm -r ../prework/lib/libflowcatch.*
mkdir build/
#mkdir build/lib
cd build/
cmake ..
#make VERBOSE=1
#./configure --prefix=/home/victor/Myfile/cafkeyproj/tFRproj/flowcatch/tools
make
#sudo make install


