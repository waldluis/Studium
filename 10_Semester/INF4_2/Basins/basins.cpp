#include <iostream>
#include <complex>
#include <fstream>
#include <math.h>

// define roots
constexpr std::complex<double> r1(-1, 0);
constexpr std::complex<double> r2(1, 0);
constexpr std::complex<double> r3(+0.33, -0.67);

// constexpr std::complex<double> r1(1, 0);
// constexpr std::complex<double> r2(0.5 * (-1), 0.5 * ( sqrt(3)));
// constexpr std::complex<double> r3(0.5 * (-1), -0.5 * ( sqrt(3)));

int testPixel(std::complex<double> z);
inline std::complex<double> calculateF(std::complex<double> z);             // inline should be faster
inline std::complex<double> calculateDerivative(std::complex<double> z);
inline std::complex<double> calculateSecondDerivative(std::complex<double> z);


/** Main function of the program.
 *
 * This function creates a PPM image file named `log.ppm` that contains the basins of attraction
 * of the roots of the polynomial f(z) = (z - r1) * (z - r2) * (z - r3).
 *
 * The image is created by iterating over all pixels of the image and testing each pixel
 * using the function `testPixel`. The result of the test is used to determine the color of the pixel.
 *
 * The image is created with a resolution of 400x400 pixels and covers the area from -5 to +5 in both
 * x and y directions.
 *
 * @return The exit code of the program.
 */
int main()
{
    constexpr unsigned nRow = 4000;                  // -> y
    constexpr unsigned nCol = 4000;                  // -> x
    constexpr double t = 3.0;                       // square size
    constexpr double xMin = -t;                     // x range min
    constexpr double xMax = +t;                     // x range max
    constexpr double yMin = -t;                     // y range min
    constexpr double yMax = +t;                     // y range max
    constexpr double Rx = (xMax - xMin) / nCol;     // x resolution
    constexpr double Ry = (yMax - yMin) / nRow;     // y resolution

    // create file
    std::ofstream file("log.ppm");
    file << "P3" << std::endl << nRow << " " << nCol << std::endl << "255" << std::endl;

    // iterate over all pixels an test them
    for (unsigned i = 0; i < nRow; ++i)
    {
        const double y = yMax - i * Ry;
        for (unsigned j = 0; j < nCol; ++j)
        {
            double x = xMin + j * Rx;
            std::complex<double> z(x, y);
            
            int result = testPixel(z);
            if(result == 1) // red
            {
                file << "255 0 0 ";
            }
            if(result == 2) // green
            {
                file << "0 255 0 ";
            }
            if(result == 3) // blue
            {
                file << "0 0 255 ";
            }
            if(result == 0) // white
            {
                file << "255 255 255 ";
            }
            if(result == 4) // black
            {
                file << "0 0 0 ";
            }
        }
        file << std::endl;
    }
    file.close();
    return 0;
}


/** Tests a pixel represented by a complex number.
 *
 * This function takes a complex number `z` as input and performs some tests on it.
 * It returns an integer value as the result of the tests.
 *
 * @param z The complex number representing the pixel to be tested.
 * @return An integer value representing the result of the tests.
 */
int testPixel(std::complex<double> z)
{
    constexpr int m = 1000;                                  // maximum number of iterations
    constexpr double eps = 1e-3;                            // margin to the roots

    std::complex<double> f_z = calculateF(z);               // value of the function F
    std::complex<double> ff_z = calculateDerivative(z);     // value of the derivative of F
    // std::complex<double> fff_z = calculateSecondDerivative(z); // value of the second derivative of F
    // std::complex<double> N = z - f_z / ff_z;                // Newton iteration value of z

    std::complex<double> N2 = z + (z * (std::complex<double>(1, 0) - 1.0 * z*z) * 0.5);
    // std::complex<double> h2 = z - (f_z * ff_z) / (ff_z * ff_z -f_z * fff_z);

    for (int i = 0; i < m; i++)
    {
        if (abs(N2 - r1) < eps)          // paint red
        {
            return 1;
        }
        if (abs(N2 - r2) < eps)          // paint green
        {
            return 2;
        }
        // if (abs(N - r3) < eps)          // paint blue
        // {
        //     return 3;
        // }

        if (abs(N2) > 30)                // paint black
        {
            return 4;
        }

        // calculate new N
        // f_z = calculateF(N);
        // ff_z = calculateDerivative(N);
        // N = N - f_z / ff_z;

        // fff_z = calculateSecondDerivative(h2);
        // h2 = h2 - (f_z * ff_z) / (ff_z * ff_z -f_z * fff_z);

        N2 = N2 +( N2 * (std::complex<double>(1, 0) - 1.0 * N2*N2) * 0.5);

    }

    return 0;                           // paint white
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


inline std::complex<double> calculateSecondDerivative(std::complex<double> z)
{
    return -2.0 * (r1 + r2 + r3 - 3.0 * z);
}


