@echo off
make game -static -console run code/GLOBALS/*.cpp code/pointClass/*.cpp code/ballClass/*.cpp
start cmd /k game.exe