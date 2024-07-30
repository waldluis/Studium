#!/bin/bash

# Variable for Size of Set
SIZE=10000

# compile both files
g++ basin_farmer.cpp -O2 -Wall -o basin_farmer.exe
g++ basin_worker.cpp -O2 -Wall -o basin_worker.exe

# Execute farmer
# Farmer creates GNU-Parallel bash-File
./basin_farmer.exe $SIZE

# Execute worker with GNU-Parallel
chmod +x parallel.sh

# Execute parallel.sh
time ./parallel.sh

# Save shared memory to file
# Delete shared memory
rm -rf basin.ppm
echo "P3" >> basin.ppm
echo $SIZE $SIZE >> basin.ppm
echo "255" >> basin.ppm
cat /dev/shm/myshm >> basin.ppm
rm -rf /dev/shm/myshm