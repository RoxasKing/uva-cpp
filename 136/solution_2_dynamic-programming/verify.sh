#!/bin/sh

g++ -std=c++11 -o main main.cpp -lm -Wall

./main < data.in > data.out

if diff -qZ data.out expected.out; then
	if [ -f "diff.out" ]; then
		rm diff.out
	fi
	echo "Accepted"
else 
	diff data.out expected.out > diff.out
	echo "Wrong Answer" 
fi

rm main
