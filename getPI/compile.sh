#!/bin/sh
# Loads omp.h header and Compiles your OpenMP program

echo "Enter you OpenMP program filename (without extension): "
read filename

clang -Xclang\
    -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include\
    -lomp "$filename.c" -o "$filename"

./"$filename"