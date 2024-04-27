#include <iostream>

const unsigned int N = 6;
unsigned A[N];

int main()
{
    for (unsigned i = 0; i < N; ++i)
    {
        A[i] = 1;
    }

    unsigned m = 1;
    unsigned z = 0;
    unsigned number = 1;

    do
    {

#if 1
        std::cout << number << ": {";
        for (unsigned i = 0; i < m; ++i)
        {
            std::cout << A[i] << (i < m - 1 ? ", " : "");
        }
        std::cout << "}" << std::endl;
        number++;
#endif

        z = A[m - 1];
        A[m - 1] = 1;
        m += z - 1;
        A[m - 1] += 1;

    } while (m >= 1);
}
