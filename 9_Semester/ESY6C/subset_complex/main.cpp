#include <iostream>
#include "subset.h"
#include <fstream>

int main()
{
    Subset subset;
    const int iMAX = 10000;
    const int iMIN = 0;
    const double xMAX = 1.6;
    const double yMIN = -1.6;
    const double xMIN = -1.6;
    const double T = (xMAX - xMIN) / (iMAX - iMIN);

    double x, y = 0;

    std::ofstream file("log.pgm");
    file << "P1" << std::endl << iMAX << " " << iMAX << std::endl << iMAX << std::endl;          // Portable Bitmap Header

    for (int i = iMIN; i < iMAX; i++)                                       // Iterate through area
    {
        y = yMIN + (i - iMIN) * T;
        for (int j = iMIN; j < iMAX; j++)
        {
            x = xMIN + (j - iMIN) * T;
            
            std::complex<double> z(x, y);

            bool isInRange = subset.f(z);

            if(isInRange)
            {
                file << "1 ";
            }
            else
            {
                file << "0 ";
            }

            // int number = subset.f_gray(z);
            // file << number << " ";
        }
        file << std::endl;
    }

    file.close();
    return 0;
}
