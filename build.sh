#!/bin/bash

if [[ $1 == "linux" ]]
then
    vendor/Linux/premake5 gmake
else
    vendor/Windows/premake5.exe gmake
fi

if [[ $1 == "linux" && $2 == "release" ]]
then
    make config=release_linux
    cp -r assets bin/Release-linux
    ./bin/Release-linux/Game
elif [[ $1 == "windows" && $2 == "release" ]]
then
    make config=release_windows
    cp -r assets bin/Release-windows
    ./bin/Release-windows/Game.exe
elif [[ $1 == "linux" && $2 == "debug" ]]
then
    make config=debug_linux
    cp -r assets bin/Debug-linux
    ./bin/Debug-linux/Game
elif [[ $1 == "windows" && $2 == "debug" ]]
then
    make config=debug_windows
    cp -r assets bin/Debug-windows
    ./bin/Debug-windows/Game.exe
fi
