#include "ball.hpp"
#include "point.hpp"
#include "quick_sort.hpp"
#include "mu_test.h"
#include "utils.hpp"
#include <iostream>
#include <cassert>

BEGIN_TEST(quick_sort_int)
    int v[] = {1, 3, 7, 11, 5, 8, 2, 9};
    int e[] = {1, 2, 3, 5, 7, 8, 9, 11};
    (void)e;
    const size_t n = sizeof(v)/sizeof(*v);
    std::cout << "\n\nbefore sorting: "<< std::endl;
    cpp::printArray(v, n);   
    printf("array length: %ld\n\n", n);
    cpp::quickSort(v, n);
    std::cout << "after sorting: "<< std::endl;
    cpp::printArray(v, n); 

    for(size_t i = 0; i < sizeof(e)/ sizeof(*v); i++)
    {
        ASSERT_EQUAL(v[i], e[i]);
    }

    ASSERT_PASS();

END_TEST   

BEGIN_TEST(quick_sort_char)
    char word[] = "cbdafyeihgjmlnpksrqovutxwz";
    char sortedWord[] = "abcdefghijklmnopqrstuvwxyz";
    std::cout << "\n\nbefore sorting: "<< std::endl;
    cpp::printArray(word, strlen(word));   
    printf("word length: %ld\n\n", strlen(word));
    printf("sortedWord length: %ld\n\n", strlen(sortedWord));

    cpp::quickSort(word, strlen(word));
   
    std::cout << "after sorting: "<< std::endl;
    cpp::printArray(word, strlen(word)); 
    printf("string length: %ld\n\n", strlen(word));
    for(size_t i = 0; i < strlen(sortedWord); i++)
    {
        ASSERT_EQUAL(word[i], sortedWord[i]);
    }

    ASSERT_PASS();

END_TEST   



BEGIN_TEST(quick_sort_array_of_points_by_radius)
    using cpp::Ball;

    Ball b1("red", 2.3);
    Ball b2("blue", 3.3);
    Ball b3("green", 1.7);
    Ball balls[] = {b1, b2, b3};
    quickSort(balls, 3);
    ASSERT_EQUAL(balls[0].getRadius(), 1.7);
    ASSERT_EQUAL(balls[1].getRadius(), 2.3);
    ASSERT_EQUAL(balls[2].getRadius(), 3.3);
    std::cout << balls[0].getRadius() << std::endl;
    std::cout << balls[1].getRadius() << std::endl;
    std::cout << balls[2].getRadius() << std::endl;
    
END_TEST

BEGIN_TEST(quick_sort_array_of_coordinates_in_the_plane)
    using cpp::Point;

    Point<double> p1(12.0, 5.0);
    Point<double> p2(4.0, 3.0);
    Point<double> p3(8.0, 6.0);
    Point<double> zero(0.0, 0.0);

    Point<double> arr[] = {p1, p2, p3};

    std::cout << "\nbefore sorting \n" << std::endl;
    
    std::cout << arr[0].getX() << " " << arr[0].getY() << " distance from (0.0): " << p1.distance(arr[0], zero) << std::endl;
    std::cout << arr[1].getX() << " " << arr[1].getY() << " distance from (0.0): " << p2.distance(arr[1], zero) << std::endl;
    std::cout << arr[2].getX() << " " << arr[2].getY() << " distance from (0.0): " << p3.distance(arr[2], zero) << std::endl;

    ASSERT_EQUAL (p1.distance(arr[0], zero), 13.0);
    ASSERT_EQUAL (p2.distance(arr[1], zero), 5.0);
    ASSERT_EQUAL (p3.distance(arr[2], zero), 10.0);

    cpp::quickSort(arr, 3);

    std::cout << "\nafter sorting \n" << std::endl;

    std::cout << arr[0].getX() << " " << arr[0].getY() << " distance from (0.0): " << p1.distance(arr[0], zero) << std::endl;
    std::cout << arr[1].getX() << " " << arr[1].getY() << " distance from (0.0): " << p2.distance(arr[1], zero) << std::endl;
    std::cout << arr[2].getX() << " " << arr[2].getY() << " distance from (0.0): " << p3.distance(arr[2], zero) << std::endl;
        
    ASSERT_EQUAL (p1.distance(arr[0], zero), 5.0);
    ASSERT_EQUAL (p2.distance(arr[1], zero), 10.0);
    ASSERT_EQUAL (p3.distance(arr[2], zero), 13.0);
    (void)arr;
    ASSERT_PASS();
    
END_TEST


int intCmpFunc(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

BEGIN_TEST(library_quick_sort_int_with_rand_num)
    const size_t N = 1000000;

    int* arr = randIntArr(N);
    int* copy = new int[N];

    for(size_t i = 0; i < N; ++i)
    {
        copy[i] = arr[i] = rand() % 10;
    }

    std::qsort(arr, N, sizeof(int), intCmpFunc);
    std::qsort(copy, N, sizeof(int), intCmpFunc);

    for(size_t i = 0; i < N; ++i)
    {
        
        ASSERT_EQUAL(copy[i], arr[i]);
    }

    delete[] arr;
    delete[] copy;

END_TEST  


BEGIN_TEST(my_quick_sort_int_with_rand_num)
    const size_t N = 100000;

    int* arr = randIntArr(N);
    int* copy = new int[N];
    
    for(size_t i = 0; i < N; ++i)
    {
        copy[i] = arr[i] = rand();
    }

    cpp::quickSort<int>(arr, N);
    cpp::quickSort<int>(copy, N);

    for(size_t i = 0; i < N; ++i)
    {
        
        ASSERT_EQUAL(copy[i], arr[i]);
    }

    delete[] arr;
    delete[] copy;

END_TEST 



BEGIN_SUITE(quick_sort_unit_tests)
    TEST(quick_sort_int)
    TEST(quick_sort_char)
    TEST(quick_sort_array_of_points_by_radius)
    TEST(quick_sort_array_of_coordinates_in_the_plane)
    TEST(library_quick_sort_int_with_rand_num)
    TEST(my_quick_sort_int_with_rand_num)
    
END_SUITE