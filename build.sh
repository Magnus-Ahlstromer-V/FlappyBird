#!/bin/bash

vendor/premake5 gmake

if [[ $1 == "release" ]]
then
    make config=release
    ./bin/Release/Game
else
    make
    ./bin/Debug/Game
fi
