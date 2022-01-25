#include "../../../work/inc/mu_test.h"
#include "../../../work/inc/stack.hpp"


// c strongly typed , weakly checked
// c++ strongly typed , strongly checked

BEGIN_TEST(stack_is_empty)
const int n = 100;
    Stack stack(n);
    ASSERT_EQUAL(stack.isEmpty(), 1);
    for (int i = 1; i <= n; i++){
        stack.push(i);
        
    }
    ASSERT_THAT(stack.isFull());
    ASSERT_THAT(!stack.isEmpty());

    stack.empty();

    ASSERT_THAT(stack.isEmpty());
    ASSERT_THAT(!stack.isFull());
    
END_TEST


BEGIN_TEST(poping_pushing_test)
const int n = 10;
    Stack stack(n);
    ASSERT_EQUAL(stack.size(),0);
    for (int i = 1; i <= n; i++){
        stack.push(i);
        ASSERT_EQUAL(stack.size(),i);

    }
    for (int i = n; i >=1; i++){
        ASSERT_EQUAL(stack.pop(), i);
        ASSERT_EQUAL(stack.size(),i-1);

    }
END_TEST


BEGIN_TEST(stack_is_full)
const int n = 10;
    Stack stack(n);
    ASSERT_THAT(stack.isEmpty());
    for (int i = 1; i <= n; i++){
        stack.push(i);
    }
    ASSERT_THAT(stack.isFull());
    stack.dump();
END_TEST

BEGIN_TEST(stack_size)
const int n = 10;
    Stack stack(n);
    ASSERT_THAT(stack.isEmpty());
    for (int i = 1; i <= n; i++){
        stack.push(i);
        ASSERT_THAT(stack.size() == i);
    }
    stack.dump();
END_TEST

BEGIN_TEST(stack_destroy)
const int n = 10;
    Stack stack(n);
    ASSERT_THAT(stack.isEmpty());
    for (int i = 1; i <= n; i++){
        stack.push(i);
    }
    ASSERT_THAT(stack.isFull());
    stack.~Stack();
    ASSERT_THAT(stack.isEmpty());
    stack.dump();
END_TEST

BEGIN_SUITE(stacks tests)
    TEST(stack_is_empty)
    TEST(poping_pushing_test)
    TEST(stack_is_full)
    TEST(stack_size)
    TEST(stack_destroy)
END_SUITE
