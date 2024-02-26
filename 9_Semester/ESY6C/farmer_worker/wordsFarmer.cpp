#include "wordsFarmer.h"

/// @brief Constructor for wordsFarmer class
/// @param nAll Amount of digits in Word
/// @param nPrefix Lenght of prefix created by farmer
WordsFarmer::WordsFarmer(unsigned nAll, unsigned nPrefix)
{
    nAll_ = nAll; 
    nPrefix_ = nPrefix;
    words_ = new unsigned [nPrefix_];
}


/// @brief Prints all prefix of words to be completed by wordsWorker-class
/// @param i The current index of the word being formed.
void WordsFarmer::printWords(unsigned i)
{
    if (i == nPrefix_)
    {
        #if 1
        std::cout << praefix_;
        for(unsigned j = 0; j < nPrefix_; j++)
        {
            std::cout << words_[j];
        }
        std::cout << " " << nAll_ << std::endl;
        #endif
        return;
    }

    for (unsigned k = 0; k < maxDigit_; k++)
    {
        words_[i] = k;
        printWords(i + 1);
    }
}
