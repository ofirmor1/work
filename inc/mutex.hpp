#ifndef MUTEX_HPP
#define MUTEX_HPP

#include<pthread.h>

namespace mt
{

class Mutex 
{

public:
    explicit Mutex();
    ~Mutex();
    
    void lock();
    void unlock();

private:
    Mutex(Mutex const& a_source); //no imp by design
	Mutex& operator=(Mutex const& a_source);

private:
    pthread_mutex_t m_mtx;
};

}//namespace mt

#endif /*#ifndef MUTEX_HPP*/