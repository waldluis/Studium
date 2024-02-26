#include "ternary_words.h"

void TernaryWords::writeWordsHelper(int i)   // i currently at end of word
{
    if (i == n_)                            // if at end of word
    {
        #if 0                               // if 1 print words, if 0 don't print words --> timing
        for (int j = 0; j < n_; j++)        // loop through word, starting at left side
        {
            std::cout << words_[j];         // print each character
        }
        std::cout << std::endl;
        #endif
        return;
    }

    for (int k = 0; k < maxDigit_; k++)             // loop until max of single digit value is reached
    {
        words_[i] = k;                      // set current character to k
        writeWordsHelper(i + 1);            // call function with next character --> recursion
    }
}
