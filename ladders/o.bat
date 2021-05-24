@echo off
g++ -std=c++11 -o tmp.exe %1
echo running...
echo ------- Run ------- >> out.txt
tmp.exe >> out.txt
