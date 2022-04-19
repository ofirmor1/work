#include "mu_test.h"
#include "crossword_puzzle.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>


BEGIN_TEST(test)
using namespace iq;
    std::string a_gridpFileath = "puzzle.txt";
    std::string a_wordsFilePath = "words.txt";
    Grid g(a_wordsFilePath, a_gridpFileath, "ud");
    g.printWordsFrequency();
    ASSERT_PASS();

END_TEST

BEGIN_SUITE(iq_tests)
    TEST(test)

END_SUITE