#include <complex>

class Subset
{
private:
    const std::complex<double> c_ = std::complex<double>(-0.751, 0.02225);
    // const std::complex<double> c_ = std::complex<double>(-0.75, 0);      // for development
    bool isInRange_ = true;
    const double L_ = 2.0;
    const int N = 1000;

public:
    bool f(std::complex<double> z);
    int f_gray(std::complex<double> z);
};
