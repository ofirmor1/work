#include "mu_test.h"
#include "file_utils.hpp"
#include <iostream>
#include <iomanip>

using namespace cpp;
using std::setw;

BEGIN_TEST(file_utils_check_frequency_print_table)
    std::map<char, int> frequency;
    frequency = letterFrequency("/home/ofir/work/test/file_utils/book.txt");
    std::cout << "The Frequency of the capital letters are: \n" << std::endl;
	for(char caps = 'A'; caps <= 'Z'; caps++)
	{
		std::cout << "Letter " << caps << " is " << setw(4) << frequency[caps] << " times." << std::endl;
	}

	std::cout << "The Frequency of the lower case letters are: \n" << std::endl;
	for(char lower = 'a'; lower <= 'z'; lower++)
	{
		std::cout << "Letter " << lower << " is " << setw(4) << frequency[lower] << " times." << std::endl;
	}

    ASSERT_EQUAL(frequency['Q'], 34);

END_TEST   

// BEGIN_TEST(count_N_most_frequncy)
//     std::map<char, int> frequency;
    

// END_TEST


BEGIN_SUITE(file_utils_tests)
    TEST(file_utils_check_frequency_print_table)
    // TEST(count_N_most_frequncy)

END_SUITE