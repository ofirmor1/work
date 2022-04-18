#include "mu_test.h"
#include "crossword_puzzle.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>


BEGIN_TEST(test)
using namespace iq;
    std::string path = "puzzle.txt";
    std::string word = "apple";
    Grid g(path);
    g.searchWord(word);
    g.printWordsFrequency();
END_TEST

BEGIN_SUITE(iq_tests)
    TEST(test)

END_SUITE