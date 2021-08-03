#!/bin/sh

g++ -std=c++11 -o main main.cpp -lm -Wall

./main > data.out

if diff -Z data.out expected.out; then
	echo "Accepted"
else 
	echo "Wrong Answer" 
fi

rm main
