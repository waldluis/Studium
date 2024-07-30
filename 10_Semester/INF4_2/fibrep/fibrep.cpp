#include <iostream>
#include <bitset>

/** @brief Generates the next number with no sequential 1s.
 * 
 * This function takes an unsigned integer as input and generates the next number in the sequence by performing bitwise operations.
 * 
 * @param n The current number in the sequence.
 * @return The next number in the sequence.
 */
unsigned int generateNext(unsigned int n)
{
    unsigned int mask = 0x1;
    unsigned int i = 0;

    n++;

    while (i < 32)
    {
        if ((n >> i) & mask)
        {
            if ((n >> (i + 1)) & mask)
            {
                n = n + (0x1 << i);
            }
            else
            {
                break;
            }
        }

        i += 1;
    }
    return n;
}

int main()
{
    unsigned int input = 0;

    std::cout << "Please enter a number: ";
    std::cin >> input;
    std::cout << std::endl;

    unsigned int result = generateNext(input);

    std::cout << "The next number with no sequential 1s is: " << result << " Binary: " << std::bitset<7>(result) << std::endl;

    return 0;
}