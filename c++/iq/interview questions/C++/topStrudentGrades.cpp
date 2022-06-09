#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

void topStrudentGrades(vector<int> grades, int N, int K)
{
    map<int, vector<int>, greater<int>> records;
    for(int i = 0; i < N; ++i)
    {
        records[grades[i]].push_back(i);
    }

    set<int, greater<int>> s;
    for(int i = 0; i < grades.size(); ++i)
    {
        s.insert(grades[i]);
    }

    cout << "top " << K << " student indexes with highest grades: " << endl;
    for(int i=0;i<K; i++){ 
		auto ij=s.begin();
		advance(ij,i);
        for(auto const& e: records[*ij])
        {
            cout << e << ' ';
        }
	}

}


int main()
{
    vector<int> grades = {97, 84, 82, 89, 84, 97, 95, 95, 84, 86};

    topStrudentGrades(grades, 10, 2);
}