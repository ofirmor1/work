#include "../../../work/inc/mu_test.h"
#include "../../../work/inc/stack.hpp"


// c strongly typed , weakly checked
// c++ strongly typed , strongly checked

BEGIN_TEST(stack_pushArr_popIntoArr)
    int arr1[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr2[10] = {0,0,0,0,0,0,0,0,0,0};
    Stack stack(arr1, 10);
    stack.dump();
    stack.dump();
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

BEGIN_TEST(stack_combine)
    int arr1[3] = {1,2,3};
    int arr2[7] = {4,5,6,7,8,9,10};
    Stack stack1, stack2, combStack;
    stack1.pushArr(arr1, 3);
    stack2.pushArr(arr2, 7);
    combStack = combineStacks(stack1, stack2);
    ASSERT_EQUAL(combStack.isFull(), true);
    for(int i = 0; i < 3; i++)
    {
        ASSERT_EQUAL(combStack.pop(), arr1[i]);  
    }
    for(int i = 0; i < 7; i++)
    {
        ASSERT_EQUAL(combStack.pop(), arr2[i]);  
    }
    ASSERT_THAT(combStack.isEmpty());

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
    for (int i = 1; i <= n; i++){
        stack.push(i);
    }
    for (int i = n; i > 0; i--){
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
    for (int i = 1; i <= n; i++){
        stack.pop();
    }
    ASSERT_THAT(stack.isEmpty());
    stack.dump();
END_TEST

BEGIN_SUITE(stacks tests)
    TEST(stack_pushArr_popIntoArr)
    TEST(stack_combine)
    TEST(stack_is_empty)
    TEST(poping_pushing_test)
    TEST(stack_is_full)
    TEST(stack_size)
    TEST(stack_destroy)
END_SUITE
