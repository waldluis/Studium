#include <iostream>
#include <vector>

class TernaryWords
{
public:
    TernaryWords(int n) : n_(n), words_(std::vector<unsigned int>(n)) {}        // constructor

    void writeWordsHelper(int i);           // helper function to write words

private:
    int n_;                                 // length of word
    std::vector<unsigned int> words_;       // vector of words with length n
    const int maxDigit_ = 3;               // max value of single digit 
};
