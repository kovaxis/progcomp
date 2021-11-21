@echo off
g++ -std=c++11 -o tmp.exe %1.cpp
echo running...
echo ------- Run ------- >> out.txt
tmp.exe >> out.txt
