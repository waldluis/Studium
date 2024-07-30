#include <iostream>
#include <complex>
#include <fstream>

// define roots
constexpr std::complex<double> r1(-1, 0);
constexpr std::complex<double> r2(+1, 0);
constexpr std::complex<double> r3(+1, +2);

int testPixel(std::complex<double> z);
inline std::complex<double> calculateF(std::complex<double> z);             // inline should be faster
inline std::complex<double> calculateDerivative(std::complex<double> z);

int main()
{
    constexpr unsigned n_row = 400; // -> y
    constexpr unsigned n_col = 400; // -> x
    constexpr double t = 5.0;
    constexpr double x_min = -t;
    constexpr double x_max = +t;
    constexpr double y_min = -t;
    constexpr double y_max = +t;
    constexpr double Rx = (x_max - x_min) / n_col;
    constexpr double Ry = (y_max - y_min) / n_row;

    // create file
    std::ofstream file("log.ppm");
    file << "P3" << std::endl
         << n_row << " " << n_col << std::endl << "255" << std::endl;

    for (unsigned i = 0; i < n_row; ++i)
    {
        const double y = y_max - i * Ry;
        for (unsigned j = 0; j < n_col; ++j)
        {
            double x = x_min + j * Rx;
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
    constexpr int m = 100;
    constexpr double eps = 1e-3;

    std::complex<double> f_z = calculateF(z);
    std::complex<double> ff_z = calculateDerivative(z);
    std::complex<double> N = z - f_z / ff_z;

    for (int i = 0; i < m; i++)
    {
        if (abs(N - r1) < eps)          // paint red
        {
            return 1;
        }
        if (abs(N - r2) < eps)          // paint green
        {
            return 2;
        }
        if (abs(N - r3) < eps)          // paint blue
        {
            return 3;
        }

        // calculate new N
        f_z = calculateF(N);
        ff_z = calculateDerivative(N);
        N = N - f_z / ff_z;

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
