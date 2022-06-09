#include <array>
#include <iostream>
#include <string>

class Ball
{
public:
    Ball(size_t a_radius, std::string a_color)
    : m_radius(a_radius)
    , m_color(a_color)
    {}

    virtual ~Ball() = default;

    friend void swap(Ball& obj1, Ball& obj2)
    {
        std::swap(obj1.m_radius, obj2.m_radius);
        std::swap(obj1.m_color, obj2.m_color);
    }

    Ball(Ball const& a_other)
    : m_radius(a_other.m_radius)
    , m_color(a_other.m_color)
    {}

    Ball& operator=(Ball& a_other)
    {
        swap(*this, a_other);

        return *this;
    }

    std::string color() const
    {
        return m_color;
    }

    size_t radius() const
    {
        return m_radius;
    }
private:
    size_t m_radius;
    std::string m_color;
};

std::ostream& operator<<(std::ostream& a_os, Ball const& a_ball)
{
    return a_os << "(" << a_ball.radius() << ',' << a_ball.color() << ")" << std::endl;
}

template<typename T>
void swap(T& a_first, T& a_second)
{
    T temp = a_first;
    a_first = a_second;
    a_second = temp;
}

void sortBallsArray(std::array<Ball, 7>& a_arr)
{
    size_t itBegin = 0;
    size_t itEnd = a_arr.size() - 1;
    for(size_t i = 0; i < a_arr.size() -1; ++i)
    {
        if(a_arr[i].color() == "red")
        {
            swap(a_arr[itBegin], a_arr[i]);
            ++itBegin;
        }
        else if(a_arr[i].color() == "green")
        {
            swap(a_arr[itEnd], a_arr[i]);
            --itEnd;
        }
    }
}

int main()
{
    std::array<Ball, 7> arr{
        Ball{1, "red"},
        Ball{2, "green"},
        Ball{3, "yellow"},
        Ball{4, "red"},
        Ball{5, "red"},
        Ball{6, "green"},
        Ball{7, "yellow"}
    };
    for(auto b : arr)
    {
        std::cout << b << std::endl;
    }
    sortBallsArray(arr);

    std::cout << "\n\n";

    for(auto b : arr)
    {
        std::cout << b << std::endl;
    }

}
