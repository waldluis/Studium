#include <iostream>
#include <complex>
typedef std::complex<double> Cx;

static inline
Cx f(Cx z)
{
    constexpr Cx c {-0.751, +0.02225};
    return z * z + c;
}

static inline
double abs_sqr(Cx z)
{
    return z.real() * z.real() + z.imag() * z.imag();
}

static inline
bool test( Cx z)
{
    constexpr double L = 7.0;
    constexpr double L2 = L*L;
    constexpr unsigned N = 1000;

    unsigned ct = 0;
    do
    {
        z = f(z);
        if(abs_sqr(z) > L2){return false;}
    } while (++ct < N);

    return true;
}

int main()
{
    constexpr unsigned n_row = 256;
    constexpr unsigned n_col = 256;
    constexpr double x_min = -3.0;
    constexpr double x_max = 3.0;
    constexpr double y_min = -3.0;
    constexpr double y_max = 3.0;
    constexpr double Rx = (x_max - x_min) / (n_col - 0);
    constexpr double Ry = (y_max - y_min) / (n_row - 0);
    
    for(unsigned row = 0; row < n_row; ++row)
    {
        const double y = y_min + (row - 0) * Ry;
        for(unsigned col = 0; col < n_col; ++col)
        {
            const double x = x_min + (col - 0) * Rx;
            const bool q = test(Cx{x,y});
            std::cout << (q ? "#" : ".");
        }
        std::cout << "\n";
    }
}