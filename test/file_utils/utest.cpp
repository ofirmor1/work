#include "mu_test.h"
#include "file_utils.hpp"
#include <iostream>
#include <iomanip>
#include <map>

using namespace cpp;
using std::setw;

BEGIN_TEST(file_utils_frequency_print_table)
    std::map<char, size_t> frequency;
    std::ifstream file("./book.txt");
    frequency = letterFrequency(file);

	std::cout << "The Frequency of the lower and upper letters are: \n" << std::endl;
	for(char lower = 'a'; lower <= 'z'; lower++)
	{
		std::cout << "Letter " << lower << " is " << setw(4) << frequency[lower] << " times." << std::endl;
	}

    ASSERT_PASS();

END_TEST   

BEGIN_TEST(count_word_frequency)
    WordMap w;
    std::ifstream file("./book.txt");
    size_t count = countWords(file, w);

    for (WordMap::iterator it = w.begin();it != w.end(); ++it) 
    {
        std::cout << it->first << " occurred "
        << it->second << " times.\n";
    }

    std::cout << "number of words in the book \n" << count << std::endl;
    ASSERT_PASS();

END_TEST


BEGIN_TEST(count_N_most_frequncy)

    const size_t K = 3;

    WordMap w;
    std::ifstream file("./book.txt");
    std::vector<std::pair<std::string,size_t> > vec;

    vec = topNWords(file, K);

    std::cout << "\n Top |"<< K << "| words frequency:" << std::endl;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << "\n the word: |" << vec[i].first << "| occurred "
        << vec[i].second << " times.\n";
    }
    
    ASSERT_PASS();

END_TEST


BEGIN_SUITE(file_utils_tests)
    TEST(file_utils_frequency_print_table)
    TEST(count_word_frequency)
    TEST(count_N_most_frequncy)

END_SUITE