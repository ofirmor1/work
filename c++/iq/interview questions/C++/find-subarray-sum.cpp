#include <iostream>
#include <vector>

using namespace std;

vector<int> checkForSubArraySum(vector<int> vec, int n, int s)
{
    int sum;
    vector<int> temp;
    temp.reserve(n);
    for(int i = 0; i < n; ++i)
    {
        sum = vec[i];
        for(int j = i+1; j < n; ++j)
        {   
            sum += vec[j];
            if(sum == s)
            {
                temp.push_back(i);
                temp.push_back(j);
                return temp;
            }
            else if(sum > s)
            {
                break;
            }
        }
    }
    if (sum == 0)
    {
        temp.erase(temp.begin(), temp.end());
    }
    return temp; 
}

int main()
{
    vector<int> vec = {1,3,5,4,2,6,8,4};
    vector<int> res = checkForSubArraySum(vec, 8, 16);
    if(res.size() > 0)
    {
        cout << "is exist sub array: " << endl;
        for(auto e : res)
        {
            cout << e << ' ' << endl;
        }
    }
    else
    {
        cout << "is not exist sub array!" << endl;
    }

    return 0;
}