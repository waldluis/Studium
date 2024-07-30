#include <iostream>
#include <complex>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cassert>
#include <sys/stat.h>
#include <cstring>

// define roots
constexpr std::complex<double> r1(-1, 0);
constexpr std::complex<double> r2(+1, 0);
constexpr std::complex<double> r3(+1, +2);

int testPixel(std::complex<double> z);
inline std::complex<double> calculateF(std::complex<double> z); // inline should be faster
inline std::complex<double> calculateDerivative(std::complex<double> z);

int main(int argc, char **argv)
{
    unsigned number = std::stoi(argv[1]); // number of line to write to
    double y = std::stod(argv[2]);        // y value (real part of complex number)
    double xMax = std::stod(argv[3]);    // x and y max value
    double xMin = -xMax;                 // x and y min value
    unsigned iMax = std::stoi(argv[4]);   // number of lines and columns
    const double Rx = (xMax - xMin) / iMax;
    const unsigned lineLenght = 12 * iMax +1;                                              // iMax Characters with whitespaces inbetween and \n
    char line[lineLenght];                                                                // line to write to SHM

    // strings for colors
    const std::string red("255   0   0 ");
    const std::string green("  0 255   0 ");
    const std::string blue("  0   0 255 ");
    const std::string white("255 255 255 ");

    // open SHM
    const int memorySize = (iMax * 12 + 1) * iMax;                                         // iMAX * 2 +1 for 0/1, whitespaces and one \n
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    char *shm = static_cast<char*>(mmap(NULL, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));      // SHM opened as char array

    if (fd == -1)
    {
        std::cout << "shm_open2 failed" << std::endl;
        return -1;
    }

    for (unsigned j = 0; j < iMax; ++j)
    {
        double x = xMin + j * Rx;
        std::complex<double> z(x, y);

        int result = testPixel(z);
        if (result == 1) // red
        {
            // red.copy(&line[j * 12], 12);
            memcpy(&line[j * 12], red.c_str(), 12);
        }
        if (result == 2) // green
        {
            // green.copy(&line[j * 12], 12);
            memcpy(&line[j * 12], green.c_str(), 12);
        }
        if (result == 3) // blue
        {
            // blue.copy(&line[j * 12], 12);
            memcpy(&line[j * 12], blue.c_str(), 12);
        }
        if (result == 0) // white
        {
            // white.copy(&line[j * 12], 12);
            memcpy(&line[j * 12], white.c_str(), 12);
        }
    }
    line[lineLenght - 1] = '\n';
    memcpy(&shm[number * lineLenght], line, lineLenght);
}

int testPixel(std::complex<double> z)
{
    constexpr int m = 100;
    constexpr double eps = 1e-3;

    std::complex<double> f_z = calculateF(z);
    std::complex<double> ff_z = calculateDerivative(z);
    std::complex<double> N = z - f_z / ff_z;

    for (int i = 0; i < m; i++)
    {
        if (abs(N - r1) < eps) // paint red
        {
            return 1;
        }
        if (abs(N - r2) < eps) // paint green
        {
            return 2;
        }
        if (abs(N - r3) < eps) // paint blue
        {
            return 3;
        }

        // calculate new N
        f_z = calculateF(N);
        ff_z = calculateDerivative(N);
        N = N - f_z / ff_z;
    }

    return 0; // paint white
}

/** Calculates the value of the function F for a given complex number.
 *
 * @param z The complex number for which to calculate the value of F.
 * @return The calculated value of F for the given complex number.
 */
inline std::complex<double> calculateF(std::complex<double> z)
{
    return (z - r1) * (z - r2) * (z - r3);
}

/**
 * Calculates the derivative of a complex number.
 *
 * @param z The complex number for which the derivative is calculated.
 * @return The derivative of the complex number.
 */
inline std::complex<double> calculateDerivative(std::complex<double> z)
{
    return (z - r1) * (z - r2) + (z - r2) * (z - r3) + (z - r1) * (z - r3);
}