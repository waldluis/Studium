#include "ternary_words.h"
#include <iostream>

// ~ 27 cycles per word with vector

int main()
{
    TernaryWords test = TernaryWords(19);

    test.writeWordsHelper(0);

    return 0;
}