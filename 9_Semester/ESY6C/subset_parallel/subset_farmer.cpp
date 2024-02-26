#include <iostream>
#include <fstream>
#include <complex>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include "sys/mman.h"
#include "sys/stat.h"
#include <string>


/// @brief Farmer for Julien Set to calculate a subset of the area3
/// @param argc 
/// @param argv Size of area to calculate
/// @return 
int main(int argc, char **argv)
{
    const int iMAX = std::stoi(argv[1]);                                // number of lines and columns
    const int iMIN = 0;
    const double xMAX = 1.6;
    const double yMIN = -1.6;
    const double xMIN = -1.6;
    const double T = (xMAX - xMIN) / (iMAX - iMIN);                  // Constant for calculating x (mapping x to i)

    double y = 0;

    // open SHM for worker
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        std::cout << "shm_open failed" << std::endl;
        return -1;
    }

    int memorySize = (iMAX * 2 + 1) * iMAX;                                 // iMAX * 2 +1 for 0/1, whitespaces and one \n 

    assert(0 == ftruncate(fd, memorySize));

    std::ofstream file("parallel.sh");
    file << "#!/bin/bash" << std::endl;                                     // Write bash script header
    file << "parallel <<EOF" << std::endl;                                  // Write parallel command
    
    // Write script to parallel execute subset_worker
    for (int i = iMIN; i < iMAX; i++)                                       // Iterate through area
    {
        y = yMIN + (i - iMIN) * T;
        file << "./subset_worker.exe " << i << " " << y << " " << xMAX << " " << iMAX <<  std::endl;
    }
    file << "EOF" << std::endl;
    file.close();
    return 0;
}
