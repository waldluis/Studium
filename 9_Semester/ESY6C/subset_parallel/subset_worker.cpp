#include <iostream>
#include <string>
#include <complex>
#include "sys/mman.h"
#include "sys/stat.h"
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <cassert>


void testComplex(double y, double xyMAX, unsigned iMAX, int number);


/// @brief Worker for Julien Set to calculate one line of the area
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char **argv)
{
    unsigned number = std::stoi(argv[1]);                           // number of line to write to
    double y = std::stod(argv[2]);                                  // y value (real part of complex number)
    double xyMAX = std::stod(argv[3]);                              // x and y max value
    unsigned iMAX = std::stoi(argv[4]);                             // number of lines and columns

    testComplex(y, xyMAX, iMAX, number);

    return 0;
}

/// @brief Function to test if numbers with given real part are in the julia set
/// @param y real part of complex number to test
/// @param xyMAX max value for real and imaginary part
/// @param iMAX Steps to calculate from -xyMAX to xyMAX
/// @param number Line number to write to
void testComplex(double y, double xyMAX, unsigned iMAX, int number)
{
    const std::complex<double> c_ = std::complex<double>(-0.751, 0.02225);           // -0.751 + 0.02225i  
    const double L_ = 2.0;
    const int N = 1000;                                                             // Depth of testing
    const int iMIN = 0;
    const double xMIN = -xyMAX;
    const double T = (xyMAX - xMIN) / (iMAX - iMIN);                                        // Constant for calculating x (mapping x to i)
    double x = 0;
    const unsigned lineLenght = 2 * iMAX +1;                                              // iMax Characters with whitespaces inbetween and \n
    char line[lineLenght];                                                                // line to write to SHM

    // open SHM
    const int memorySize = (iMAX * 2 + 1) * iMAX;                                         // iMAX * 2 +1 for 0/1, whitespaces and one \n
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    char *shm = static_cast<char*>(mmap(NULL, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));      // SHM opened as char array

    if (fd == -1)
    {
        std::cout << "shm_open2 failed" << std::endl;
        return;
    }

    for (unsigned j = iMIN; j < iMAX; j++)
    {
        x = xMIN + (j - iMIN) * T;
        bool isInRange = true;

        std::complex<double> z(x, y);
        std::complex<double> Fn = z * z + c_;                                       // Initial Fn

        for (int k = 0; k <= N; k++)
        {
            if (Fn.real() * Fn.real() + Fn.imag() * Fn.imag() > L_ * L_)            // Check if Fn is in the range if L_
            {
                isInRange = false;
                break;
            }
            Fn = Fn * Fn + c_; // Next Fn based on old Fn
        }

        // Write result to line variable
        if (isInRange)
        {
            line[j * 2] = '1';
        }
        else
        {
            line[j * 2] = '0';
        }
        line[j * 2 + 1] = ' ';
    }
    line[lineLenght - 1] = '\n';
    memcpy(&shm[number * lineLenght], line, lineLenght);
}