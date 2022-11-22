#include "utils.hpp"

namespace home
{

std::string timeNow()
{
    using namespace std;

    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = std::chrono::system_clock::to_time_t(end);

    string time_now = ctime(&end_time);
    int i = time_now.size();
    time_now.resize(i - 1); 
    return time_now;
}


}//namespace home
