#ifndef MUTEX_HPP
#define MUTEX_HPP

#include<pthread.h>

namespace mt
{

class Mutex 
{

public:
    Mutex();
    ~Mutex();
    
    void lock();
    void unlock();

    bool isLock() const;

private:
    Mutex(Mutex const& a_source); //no imp by design
	Mutex& operator=(Mutex const& a_source);

private:
    pthread_mutex_t m_mtx;
    bool m_isLock;
};

}//namespace mt

#endif /*#ifndef MUTEX_HPP*/