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
    pthread_mutex_t m_mtx;
    bool m_isLock;
};

}//namespace mt

#endif /*#ifndef MUTEX_HPP*/