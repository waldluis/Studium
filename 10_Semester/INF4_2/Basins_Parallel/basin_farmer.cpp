#include <iostream>
#include <complex>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cassert>
#include <sys/stat.h>


int main(int argc, char **argv)
{
    const unsigned iMax = std::stoi(argv[1]); // -> max x & y
    const unsigned iMin = 0;                  // -> min x & y  
    constexpr double t = 5.0;  
    constexpr double xMax = +t;
    constexpr double yMin = -t;
    constexpr double yMax = +t;
    const double Ry = (yMax - yMin) / iMax;               



    // open SHM for worker
    // open SHM for worker
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        std::cout << "shm_open failed" << std::endl;
        return -1;
    }

    int memorySize = (iMax * 12 + 1) * iMax;                                 // iMAX * 12 +1 for RGB, whitespaces and one \n 

    assert(0 == ftruncate(fd, memorySize));

    std::ofstream file("parallel.sh");
    file << "#!/bin/bash" << std::endl;                                     // Write bash script header
    file << "parallel <<EOF" << std::endl;                                  // Write parallel command
    
    // Write script to parallel execute subset_worker
    for (unsigned i = iMin; i < iMax; i++)                                       // Iterate through area
    {
        const double y = yMax - i * Ry;
        file << "./basin_worker.exe " << i << " " << y << " " << xMax << " " << iMax <<  std::endl;
    }
    file << "EOF" << std::endl;
    file.close();
    return 0;
}