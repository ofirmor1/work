#include <stddef.h>
#include <iostream>
#include <vector>
#include <algorithm>

void removeDuplicates(std::vector<int>& a_vec)
{
    auto last = std::unique(a_vec.begin(), a_vec.end());
    a_vec.erase(last, a_vec.end());
}


int main()
{
    std::vector<int> vec = {1,2,3,4,4,5,5,5,6,9};
    removeDuplicates(vec);

    for(auto const& e : vec)
    {
        std::cout << e << " ";
    }
    return 0;
}