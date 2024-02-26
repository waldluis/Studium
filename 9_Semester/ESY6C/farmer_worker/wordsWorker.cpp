#include "wordsWorker.h"

/// @brief Constructor for wordsWorker class
/// @param n Amount of Digits to be created
/// @param praefix Prefix created by Farmer
WordsWorker::WordsWorker(unsigned n, std::string praefix)
{
    n_ = n;
    praefix_ = praefix; 
    words_ = new unsigned [n_];
}


/// @brief Prints all possible combinations of words formed by a prefix and digits.
/// @param i The current index of the word being formed.
void WordsWorker::printWords(unsigned i)
{
    if (i == n_)
    {
        #if 1
        std::cout << praefix_;
        for(unsigned j = 0; j < n_; j++)
        {
            std::cout << words_[j];
        }
        std::cout << std::endl;
        #endif
        return;
    }

    for (unsigned k = 0; k < maxDigit_; k++)
    {
        words_[i] = k;
        printWords(i + 1);
    }
}
