#include <iostream>

#define PRINT 0

const int N = 6;
const int k = 2;
int counter = 0;

/**
 * Shifts the elements of an array to the left by one position.
 *
 * @param A - Pointer to the array.
 */
void shiftArrayLeft(int *A)
{
    int temp = A[0];
    for (int i = 0; i < N - 1; ++i)
    {
        A[i] = A[i + 1];
    }
    A[N - 1] = temp;
}

/** Compares two arrays of integers.
 *
 * This function takes two arrays of integers, A and B, and compares them element by element.
 * It returns true if all elements in both arrays are equal, and false otherwise.
 *
 * @param A The first array to compare.
 * @param B The second array to compare.
 * @return True if all elements in both arrays are equal, false otherwise.
 */
bool compareArrays(const int *A, const int *B)
{
    for (int i = 0; i < N; ++i)
    {
        if (A[i] != B[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * Compares two arrays lexicographically.
 *
 * This function compares two arrays `A` and `B` lexicographically. It returns true if `A` is lexicographically less than `B`,
 * and false otherwise. The comparison is performed element by element, starting from the first element of each array.
 *
 * @param A The first array to compare.
 * @param B The second array to compare.
 * @return True if `A` is lexicographically less than `B`, false otherwise.
 */
bool lexCompareArrays(int A[], int B[])
{
    for (int i = 0; i < N - 1; ++i)
    {
        if (A[i] > B[i])
        {
            return false;
        }
        else if (A[i] < B[i])
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    return true;
}

/**
 * Compares two arrays lexicographically.
 * 
 * @param A Pointer to the first array.
 * @param B Pointer to the second array.
 * @return Negative value if A is lexicographically less than B,
 *         positive value if A is lexicographically greater than B,
 *         and 0 if A is lexicographically equal to B.
 */
int compareLex(const int *A, const int *B)
{
    for (int i = 0; i < N; ++i)
    {
        if (A[i] != B[i])
        {
            return (A[i] < B[i]) ? 1 : -1;
        }
    }
    return 0;
}

// TODO check why not working
/**
 * Compares two arrays lexicographically.
 *
 * This function compares two arrays, `A` and `B`, lexicographically. It returns `true` if `A` is lexicographically less than `B`, and `false` otherwise.
 *
 * @param A Pointer to the first array.
 * @param B Pointer to the second array.
 * @return `true` if `A` is lexicographically less than `B`, `false` otherwise.
 */
bool lexCompare(const int *A, const int *B)
{
    for (int i = 0; i < N; ++i)
    {
        if (A[i] != B[i])
        {
            return B[i] < A[i];
        }
    }
    return 0;
}

// TODO: Check numbers with oeis.org
/**
 * Compares two arrays lexicographically.
 *
 * This function compares two arrays, `A` and `B`, lexicographically. It returns `true` if `A` is lexicographically less than `B`, and `false` otherwise.
 *
 * @param A Pointer to the first array.
 * @param B Pointer to the second array.
 * @return `true` if `A` is lexicographically less than `B`, `false` otherwise.
 */
bool lexCompare2(const int *A,const int *B)
{
    int sumA = 0;
    int sumB = 0;

    // calculates the sum of the elements of the arrays
    // to compare them lexicographically
    for (int i = 0; i < N; ++i)
    {
        sumA += A[i] * (i + 1);
        sumB += B[i] * (i + 1);
    }

    return sumA > sumB;
}

/**
 * Finds the minimum lexicographically rotated sequence of integers.
 *
 * This function takes an array of integers as input and finds the minimum lexicographically
 * rotated sequence of the array elements. The minimum lexicographically rotated sequence
 * is the sequence that is obtained by rotating the array elements in such a way that the
 * resulting sequence is the smallest possible lexicographically.
 *
 * @param A The array of integers to be rotated.
 */
void minLexRotation(int *A)
{
    // A is the initial array -> must not be changed
    // B is same as A -> will be changed
    // C is the minimum lexicographically array -> initially A
    // B gets rotated and compared to C
    // if B is lexicographically smaller than C, C gets updated to B
    // repeated until back to initial array
    // if C is equal to initial array, then C is the minimum lexicographically array
    // -> output C

    int B[N];
    int C[N];
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
        C[i] = A[i];
    }

    for (int i = 0; i < N; ++i)
    {
        shiftArrayLeft(B);
        if (compareLex(B, C) == 1)
        {
            for (int i = 0; i < N; ++i)
            {
                C[i] = B[i];
            }
        }
    }

#if PRINT
    {
        for (int i = 0; i < N; ++i)
        {
            std::cout << C[i] << " ";
        }
        std::cout << std::endl;
    }
#endif

    if (compareArrays(A, C) == 1)
    {
        std::cout << "Minimum lexicographically array: ";
        for (int i = 0; i < N; ++i)
        {
            std::cout << C[i] << " ";
        }
        std::cout << std::endl;

        counter++;
    }
}

/**
 * Generates arrays in a count-up pattern.
 * This function generates arrays with elements in a count-up pattern, starting from 0 and incrementing by 1.
 * The generated arrays can be used for various purposes.
 */
void generateArraysCountUp()
{
    int A[N];
    for (int i = 0; i < N; ++i)
    {
        A[i] = 0;
    }

    while (true)
    {

#if PRINT
        {
            for (int i = 0; i < N; ++i)
            {
                std::cout << A[i] << " ";
            }
            std::cout << std::endl;
        }
#endif

        minLexRotation(A);

        int index = N - 1;

        while (index >= 0 && A[index] == k - 1)
        {
            A[index] = 0;
            --index;
        }

        if (index < 0)
        {
            break;
        }

        A[index]++;
    }
}

int main()
{
    generateArraysCountUp();

    std::cout << "Number of minimum lexicographically arrays: " << counter << std::endl;

    return 0;
}