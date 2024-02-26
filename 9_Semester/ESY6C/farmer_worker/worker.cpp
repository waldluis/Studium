#include <iostream>
#include "wordsWorker.h"
#include <string>

int main(int argc, char** argv)
{
    std::string input = argv[1];

    unsigned n = std::stoi(argv[2]);

    WordsWorker words(n - input.length(), input);           // Worker with Digits to be generated and Prefix

    words.printWords(0);

    return 0;
}