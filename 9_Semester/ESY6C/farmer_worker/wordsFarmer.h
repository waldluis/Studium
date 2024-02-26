#include <iostream>


/// @brief Class to create prefix for ternary Words
class WordsFarmer
{
private:
    unsigned nAll_;
    unsigned nPrefix_;
    unsigned *words_;
    const unsigned maxDigit_ = 3;
    std::string praefix_;

public: 
    WordsFarmer(unsigned nAll, unsigned nPraefix);
    void printWords(unsigned i);
};