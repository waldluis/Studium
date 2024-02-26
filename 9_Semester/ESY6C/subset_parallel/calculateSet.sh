#!/bin/bash

# Variable for Size of Set
SIZE=1000

# compile both files
g++ -O2 -Wall subset_farmer.cpp -o subset_farmer.exe
g++ -O2 -Wall subset_worker.cpp -o subset_worker.exe

# Execute farmer
# Farmer creates GNU-Parallel bash-File
./subset_farmer.exe $SIZE

# Execute worker with GNU-Parallel
chmod +x parallel.sh
time ./parallel.sh

# Save shared memory to file
# Delete shared memory
rm -rf set.pbm
echo "P1" >> set.pbm
echo $SIZE $SIZE >> set.pbm
cat /dev/shm/myshm >> set.pbm
rm -rf /dev/shm/myshm
