#include "mu_test.h"
#include "stack.hpp"


// c strongly typed , weakly checked
// c++ strongly typed , strongly checked

BEGIN_TEST(stack_pushArr_popIntoArr)
    int arr1[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr2[10] = {0};
    Stack stack(arr1, 10);
    stack.dump();
    ASSERT_EQUAL(stack.isFull(), true);
    stack.pushArr(arr2, 10);
    ASSERT_EQUAL(stack.size(), 10);
    for(int i = 10; i > 0; i--)
    {
        ASSERT_EQUAL(stack.pop(), i);
        
    }
    ASSERT_EQUAL(stack.isEmpty(), true);

END_TEST


BEGIN_TEST(stack_popIntoArr)
    int arr1[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr2[10] = {0};
    Stack stack(arr1, 5, 5);
    ASSERT_EQUAL(stack.isFull(), true);
    ASSERT_EQUAL(stack.isEmpty(), false);
    ASSERT_EQUAL(stack.size(), 10);
    stack.popIntoArr(arr2, 4);
    int expected[] = {5,4,3,2};
    size_t se = sizeof(expected);
    TRACE(se);
    int r = memcmp(arr2, expected, se);
    ASSERT_EQUAL(r, 0);
    
END_TEST


BEGIN_TEST(combine_one_stack_with_an_empty_stack)
    Stack empty(64);

    int source_array[] = {1,2,3,4,5,6,7,8,9};
    Stack full(source_array, sizeof(source_array)/sizeof(source_array[0])); 

    Stack r(100);     
    combineStacks(r,full, empty);
    ASSERT_EQUAL(full.size(), 0);
    ASSERT_EQUAL(empty.size(), 0);
    while(!full.isEmpty()){
            TRACER << full.pop();
    }
END_TEST


BEGIN_TEST(combine_one_stack_with_another_stack)
    Stack empty(64);

    int array[7] = {0};
    Stack first(array, sizeof(array)/sizeof(array[0]));
    
    int source_array[] = {1,2,3,4,5,6,7,8,9};
    Stack full(source_array, sizeof(source_array)/sizeof(source_array[0]));

    Stack r(100);
    combineStacks(r, full, empty);

    while(!r.isEmpty()){
        TRACER << r.pop() << " ";
    }
    ASSERT_PASS();

END_TEST


BEGIN_TEST(stack_constractors)
    int arr[3] = {1,2,3};
    Stack newStack(arr, 3, 10);
    newStack.dump();
END_TEST


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
    for (size_t i = 1; i <= n; i++){
        stack.push(i);
    }
    for (size_t i = n; i > 0; i--){
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
    for (size_t i = 1; i <= n; i++){
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
    for (int i = 1; i <= n; i++){
        stack.pop();
    }
    ASSERT_THAT(stack.isEmpty());
    stack.dump();
END_TEST

BEGIN_SUITE(stacks tests)
    TEST(stack_pushArr_popIntoArr)
    TEST(stack_is_empty)
    TEST(poping_pushing_test)
    TEST(stack_is_full)
    TEST(stack_size)
    TEST(stack_destroy)
    TEST(stack_popIntoArr)
    TEST(combine_one_stack_with_an_empty_stack)
    TEST(combine_one_stack_with_another_stack)

END_SUITE
