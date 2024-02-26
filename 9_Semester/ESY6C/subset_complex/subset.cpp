#include "subset.h"
#include <iostream>

bool Subset::f(std::complex<double> z)
{
    std::complex<double> Fn = z * z + c_;                                   // Initial Fn
    for (int k = 0; k <= N; k++)
    {
        if (Fn.real() * Fn.real() + Fn.imag() * Fn.imag() > L_ * L_)        // Check if Fn is in the range if L_
        {
            return false;
        }
        Fn = Fn * Fn + c_;                                                  // Next Fn based on old Fn
    }
    return true;
}

int Subset::f_gray(std::complex<double> z)
{
    std::complex<double> Fn = z * z + c_;                                   // Initial Fn
    for (int k = 0; k <= N; k++)
    {
        if (Fn.real() * Fn.real() + Fn.imag() * Fn.imag() > L_ * L_)        // Check if Fn is in the range if L_
        {
            return N-k;
        }
        Fn = Fn * Fn + c_;                                                  // Next Fn based on old Fn
    }
    return 0;
}
