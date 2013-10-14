# compile script for g++ using c++11 standard
# just run sh compile_mutablecode.sh

g++ -I/usr/local/include -I./include ./src/*.cpp -o ./build/mutablecode -L/usr/local/lib -std=c++11 -std=gnu++11
