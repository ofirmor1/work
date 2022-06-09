#include <iostream>
#include <thread>
#include <chrono>

class Singleton
{

public:
    Singleton(Singleton const& a_src) = delete;
    Singleton& operator=(Singleton const& a_src) = delete;
    static Singleton* getInstance(std::string const& a_value);
    std::string value() const;
    void something();

protected:
    std::string m_value;
    static Singleton* m_singleton;

protected:
    Singleton(std::string const a_value);
};

Singleton* Singleton::m_singleton = nullptr;

Singleton::Singleton(std::string const a_value)
: m_value(a_value)
{}

std::string Singleton::value() const
{
    return m_value;
}

Singleton* Singleton::getInstance(std::string const& a_value)
{
    if(m_singleton == nullptr)
    {
        m_singleton = new Singleton(a_value);
    }

    return m_singleton;
}

void threadOne()
{
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("one");
    std::cout << singleton->value() << '\n';
}

void threadTwo()
{
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("two");
    std::cout << singleton->value() << '\n';
}

int main()
{
    std::thread t1(threadOne);
    std::thread t2(threadTwo);

    t1.join();
    t2.join();

    return 0;
}