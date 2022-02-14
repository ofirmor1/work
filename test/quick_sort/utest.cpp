#include "quick_sort.hpp"
#include "ball.hpp"
#include "point.hpp"
#include "mu_test.h"
#include <iostream>
#include <cassert>

BEGIN_TEST(quick_sort_int)
    int v[] = {1, 3, 7, 11, 5, -8, 2, 9};
    int e[] = {-8, 1, 2, 3, 5, 7, 9, 11};
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
    Ball b1, b2, b3;
    b1.m_color = "red";
    b1.m_radius = 2.3;
    b2.m_color = "blue";
    b2.m_radius = 3.3;
    b3.m_color = "green";
    b3.m_radius = 1.7;
    Ball balls[] = {b1, b2, b3};
    cpp::quickSort(balls, 3);
    ASSERT_EQUAL(balls[0].m_radius, 1.7);
    ASSERT_EQUAL(balls[1].m_radius, 2.3);
    ASSERT_EQUAL(balls[2].m_radius, 3.3);
    std::cout << balls[0].m_radius << std::endl;
    std::cout << balls[1].m_radius << std::endl;
    std::cout << balls[2].m_radius << std::endl;
    
END_TEST

BEGIN_TEST(quick_sort_array_of_coordinates_in_the_plane)
    Point<double> p1, p2, p3;

    p1.x = 12.0;
    p1.y = 5.0;

    p2.x = 4.0;
    p2.y = 3.0;

    p3.x = 8.0;
    p3.y = 6.0;
    
    Point<double> zero;
    zero.x = 0;
    zero.y = 0;

    Point<double> arr[] = {p1, p2, p3};

    std::cout << "\nbefore sorting \n" << std::endl;

    std::cout << arr[0].x << " " << arr[0].y << " distance from (0.0): " << distance(arr[0], zero) << std::endl;
    std::cout << arr[1].x << " " << arr[1].y << " distance from (0.0): " << distance(arr[1], zero) << std::endl;
    std::cout << arr[2].x << " " << arr[2].y << " distance from (0.0): " << distance(arr[2], zero) << std::endl;
    
    ASSERT_EQUAL (distance(arr[0], zero), 13.0);
    ASSERT_EQUAL (distance(arr[1], zero), 5.0);
    ASSERT_EQUAL (distance(arr[2], zero), 10.0);

    cpp::quickSort(arr, 3);

    std::cout << "\nafter sorting \n" << std::endl;

    std::cout << arr[0].x << " " << arr[0].y << " distance from (0.0): " << distance(arr[0], zero) << std::endl;
    std::cout << arr[1].x << " " << arr[1].y << " distance from (0.0): " << distance(arr[1], zero) << std::endl;
    std::cout << arr[2].x << " " << arr[2].y << " distance from (0.0): " << distance(arr[2], zero) << std::endl;
        
    ASSERT_EQUAL (distance(arr[0], zero), 5.0);
    ASSERT_EQUAL (distance(arr[1], zero), 10.0);
    ASSERT_EQUAL (distance(arr[2], zero), 13.0);
    (void)arr;
    ASSERT_PASS();
    // ASSERT_EQUAL(balls[1].m_radius, 2.3);
    // ASSERT_EQUAL(balls[2].m_radius, 3.3);
    // std::cout << balls[0].m_radius << std::endl;
    // std::cout << balls[1].m_radius << std::endl;
    // std::cout << balls[2].m_radius << std::endl;
    
END_TEST


BEGIN_SUITE(quick_sort_unit_tests)
    TEST(quick_sort_int)
    TEST(quick_sort_char)
    TEST(quick_sort_array_of_points_by_radius)
    TEST(quick_sort_array_of_coordinates_in_the_plane)
    
END_SUITE