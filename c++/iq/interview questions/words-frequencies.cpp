#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
 
void printFrequency(string st)
{
    map<string, int>FW;
    stringstream ss(st);
    string Word;
 
    while (ss >> Word)
        FW[Word]++;
    
    cout << "\nwords frequencies in\n" << st << '\n'<<endl;
    for(auto const& pair : FW)
        cout << pair.first << "-> "
             << pair.second << "\n";
}
 
int main()
{
    string s ="I am who I am";
    printFrequency(s);
    return 0;
}