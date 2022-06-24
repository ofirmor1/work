#include "mu_test.h"
#include "image.hpp"
#include <iostream>

using namespace advcpp;

BEGIN_TEST(test)
    std::ofstream outputFile("cat2.ppm");
    std::ifstream originalImage("cat.ppm");
    Image img = read(originalImage);
    save(img, outputFile);
    ASSERT_PASS();
END_TEST

// BEGIN_TEST(brighten)


BEGIN_SUITE(iq_tests)
    TEST(test)

END_SUITE