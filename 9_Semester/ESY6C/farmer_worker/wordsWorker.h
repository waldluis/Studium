#include <iostream>


/// @brief Class to complete prefix for ternary words created by wordsFarmer
class WordsWorker
{
private:
    unsigned n_;
    unsigned *words_;
    const unsigned maxDigit_ = 3;
    std::string praefix_;


public:
    WordsWorker(unsigned n, std::string word);
    void printWords(unsigned i);
};