#ifndef MULTI_THREAD_UTILS_HPP
#define MULTI_THREAD_UTILS_HPP

#include "mutex.hpp"

template<typename X, typename R = mt::Mutex>
class LockGaurd{    
    LockGaurd(R& r)
    : resource(r)
    {        
        try{
            resource.lock();        
        }catch(...){
            throw X();
        }
    }
    ~LockGaurd(){
        try{
            resource.unlock();
        }catch(...){
            throw X();
        }
    }
private:
    R& resource;
};
// RAII: resource aquisition is initialization
struct Lock{
    mt::Mutex& m_mutex;
    Lock(mt::Mutex& mutex)
    : m_mutex(mutex)
    {
        m_mutex.lock();
    }
    ~Lock(){
        m_mutex.unlock();
    }
};

#endif /*ifndef MULTI_THREAD_UTILS_HPP*/