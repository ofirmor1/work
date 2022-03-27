#ifndef QUEST_HPP
#define QUEST_HPP

#include <cstddef>

namespace iq
{
void mergeArr(int *arr1, int *arr2, size_t n, size_t k);

void rotateArr(int *arr, size_t n, size_t k);

void replaceEachElmWIthLargestOnRight(int *arr, int n);

void replaceEachElmWIthClosestLargestOnRight(int *arr, int n);

int* nFirstPrime(size_t n, int* arr);

void sortArr(int* arr, size_t n);
}//namespace iq

#endif /*#ifndef QUEST_HPP*/