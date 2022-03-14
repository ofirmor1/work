#ifndef MULTI_THREAD_UTILS_HPP
#define MULTI_THREAD_UTILS_HPP

#include "mutex.hpp"

template<typename R, typename X>
class ResourceGuard{    
    ResourceGuard(R& r)
    : resource(r)
    {        
        try{
            resource.lock();        
        }catch(...){
            throw X();
        }
    }
    ~ResourceGuard(){
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
struct LockGuard{
    mt::Mutex& m_mutex;
    LockGuard(mt::Mutex& mutex)
    : m_mutex(mutex)
    {
        
        m_mutex.lock();
        
    }
    ~LockGuard(){
        m_mutex.unlock();
    }
};

#endif /*ifndef MULTI_THREAD_UTILS_HPP*/