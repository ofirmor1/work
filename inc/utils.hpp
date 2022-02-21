#ifndef UTILS_HPP
#define UTILS_HPP

#define arrSize(T) (sizeof(T)/sizeof(T[0]))

template <typename T>
//require: <
struct LessElementsCompare
{
    bool operator()(T const& a_first, T const& a_second)
    {
        return a_first < a_second;
    }
};

struct Comparator
{
    bool operator()(std::pair <std::string ,size_t> const& a, std::pair <std::string, size_t> const& b) const
    {
        return a.second < b.second;
    }
};

template<typename T, typename U>
struct GreaterPairCompare
{
      bool operator()(const std::pair<const T,U>* a,const std::pair<const T,U>* b) const
      {
            return a->second > b->second;
      }
};

template<typename T, typename U>
struct LessPairCompare
{
      bool operator()(const std::pair<const T,U>* a,const std::pair<const T,U>* b) const
      {
            return a->second < b->second;
      }
};

template <typename T>
struct LessCompareByPointer
{
    bool operator() (const T* lhs, const T* rhs) const
    {
        return *lhs < *rhs;
    }
};

template <typename T>
void swap(T& a_first, T& a_second)
{
    T temp = a_first;
    a_first = a_second;
    a_second = temp;
}

int* randIntArr(const size_t N)
{
    int* arr = new int[N];
    for(size_t i = 0; i < N; i++)
    {
        arr[i] = random() % 10;
    }
    
    return arr;
}

template <typename T>
T fRand(T fMin, double fMax)
{
    T f = (T)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template <typename T>
struct RandomGenerator
{
    T minValue;
    T maxValue;
    RandomGenerator(T a_min, T a_max)
    : minValue(a_min)
    , maxValue(a_max)
    {}

    T operator()()
    {
        return (T(rand())/RAND_MAX)*(maxValue-minValue)+minValue;
    }
};

std::map<char, int> letterFrequency(const char* a_filename);
  

#endif /*ifndef UTILS_HPP*/