#include <stdio.h>
#include "mu_test.h"
#include "min_stack.hpp"
#include "stack.hpp"

BEGIN_TEST(min_stack_tests)
    MinStack stack(5);
    stack.push(5);
    stack.push(3);
    stack.push(9);
    stack.push(23);
    stack.push(1);
    ASSERT_THAT(stack.isFull());
    ASSERT_EQUAL(stack.minVal(), 1);


END_TEST

BEGIN_SUITE(run tests on minstack)
    TEST(min_stack_tests)

END_SUITE
