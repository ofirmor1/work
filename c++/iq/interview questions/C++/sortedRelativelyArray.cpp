#include <iostream>
#include <vector>

using namespace std;

// array A
// 2 5 12 2 8 9 13 5 8 12 
// array B
// 5 2 8 12 9 
// relatively sorted array 
// 5 5 2 2 8 8 12 12 9 13 

void sortedRelativelyArray(vector<int>& a, vector<int>& b)
{
    int bStart = 0,aStart = 0,j;
    while(bStart < b.size())
    {
        j = aStart;
        while(j < a.size())
        {
            if (a[j] == b[bStart])
            {
                swap(a[j], a[aStart++]);
            }
            ++j;
        }
        ++bStart;
    }

}

int main()
{
    vector<int> vec1 = {2, 5, 12, 2, 8, 9, 13, 5, 8, 12};
    vector<int> vec2 = {5, 2, 8, 12, 9};
    sortedRelativelyArray(vec1, vec2);
    for(auto e : vec1)
    {
        cout << e << ' ';
    }
}