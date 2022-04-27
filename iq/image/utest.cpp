#include "mu_test.h"
#include "image.hpp"
#include <iostream>

BEGIN_TEST(test)
using namespace advcpp;
    size_t width = 300;
    size_t height = 300;
    std::ofstream outputFile;
    std::string imageFilpath = "cat.pgm";
    std::ifstream file(imageFilpath);
    Image image(width, height, "p2", 15);
    Image temp = read(file);
    save(temp, outputFile);
    ASSERT_PASS();
END_TEST

BEGIN_SUITE(iq_tests)
    TEST(test)

END_SUITE