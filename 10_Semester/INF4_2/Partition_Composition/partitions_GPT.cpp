#include <iostream>

const unsigned int N = 6; // Change this constant to the desired number

void generatePartitions(unsigned int arr[], unsigned int index, unsigned int num)
{
    if (num == 0)
    {
        // Print the partition
        for (unsigned int i = 0; i < index; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        return;
    }

    unsigned int start = (index == 0) ? 1 : arr[index - 1];

    for (unsigned int i = start; i <= num; i++)
    {
        arr[index] = i;
        generatePartitions(arr, index + 1, num - i);
    }
}

int main()
{
    unsigned int arr[N];
    generatePartitions(arr, 0, N);

    return 0;
}